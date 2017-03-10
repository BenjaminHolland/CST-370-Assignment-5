

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <exception>
#include <queue> //Don't wnat to implement my own queue
#include <algorithm>
#include <cstring> //Need memset
using namespace std;

class Graph{
private:

	unsigned int count;

	//unique pointers are nice since we don't have to deal with explicit memory management.
	unique_ptr<bool[]> adjacency;

public:

	//Delete the default copy constructor, since we've got a unique pointer that would need to be copied, and we don't actually need to copy a graph.
	Graph(const Graph& copy)=delete;

	//Graph Constructor that loads data from a stram. This allows for testing as well as stream validation before attempting to load.
	Graph(istream& dataStream);

	//Ouptuts the internal adjacency matrix as a string.
	string toString() const;

	//Get the number of vertecies.
	unsigned int getCount() const;

	//Sets an edge to the specified state.
	void setEdge(unsigned int from,unsigned int to,bool connected);

	//Retrieves the state of an edge.
	bool getEdge(unsigned int from,unsigned int to) const;

	//Returns a sequence of nodes in breadth-first order, begining at the given starting node.
	//NOTE: Only nodes connected to the starting nodes are searched.
	string getBFTDisplay(unsigned int startingNode){
		if(startingNode>getCount()){
			throw exception();
		}else{
			queue<unsigned int> nodesToVisit;
			bool* visited=new bool[getCount()];
			memset(visited,0,sizeof(bool)*getCount());
			nodesToVisit.push(startingNode);
			stringstream output;
			while(!nodesToVisit.empty()){
				unsigned int currentIdx=nodesToVisit.front();
				nodesToVisit.pop();
				if(!visited[currentIdx]){
					output<<currentIdx<<"->";
					visited[currentIdx]=true;
					for(unsigned int toIdx=0;toIdx<getCount();toIdx++){
						if(getEdge(currentIdx,toIdx)){
							nodesToVisit.push(toIdx);
						}
					}
				}
			}

			delete[] visited;
			string retval=output.str();
			return retval.substr(0,retval.length()-2); //O(1) truncation.
		}

	}


};


//Runs the acceptance test.
int main(int argc,char* argv[]){

	string filename;
	cout<<"Enter Filename: ";
	cin>>filename;

	ifstream data(filename);
	if(data.fail()){
		throw runtime_error("Invalid File Specified.");
	}
	unsigned int startIdx;
	cout<<"Enter a start vertex: ";
	cin>>startIdx;
	if(cin.fail()){
		throw runtime_error("Invalid Starting Index.");
	}
	Graph g(data);

	if(startIdx>=g.getCount()){
		throw runtime_error("Invalid Starting Index.");
	}
	cout<<"BSF order: "<<g.getBFTDisplay(startIdx);
}

Graph::Graph(istream& dataStream){
	//read the number of vertecies in the graph.
	dataStream>>count;
	//create a unique_pointer. This makes sure that our memory gets destroyed automatically.
	adjacency=make_unique<bool[]>(count*count);
	unsigned int state;
	for(unsigned int fromIdx=0;fromIdx<count;fromIdx++){
		for(unsigned int toIdx=0;toIdx<count;toIdx++){
			dataStream>>state;
			//cout<<"Edge from  "<<fromIdx<<" to "<<toIdx<<" "<<state<<endl;
			if(state==1){
				setEdge(fromIdx,toIdx,true);
			}
		}
	}
}

unsigned int Graph::getCount() const{
	return count;
}

string Graph::toString() const{
	stringstream out;
	for(unsigned int row=0;row<count;row++){
		for(unsigned int col=0;col<count-1;col++){
			out<<getEdge(row,col);
		}
		out<<getEdge(row,count-1)<<endl;
	}
	return out.str();
}

bool Graph::getEdge(unsigned int from,unsigned int to) const{
	if(from>=count||from<0){
			throw exception();
		}
		if(to>=count||from<0){
			throw exception();
		}
		return adjacency[from*count+to];
}

void Graph::setEdge(unsigned int from,unsigned int to,bool connected){
	if(from>=count||from<0){
			throw exception();
		}
		if(to>=count||from<0){
			throw exception();
		}
		adjacency[from*count+to]=connected;
}

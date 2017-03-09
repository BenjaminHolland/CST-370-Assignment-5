/*
 * BFS.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: Benjamin
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <exception>
using namespace std;

class Graph{
private:
	unsigned int count;

	//unique pointers are nice since we don't have to deal with explicit memory management.
	unique_ptr<bool[]> adjacency;

public:
	//Delete the default copy constructor, since we've got a unique pointer that would need to be copied, and we don't actually need to copy a graph.
	Graph(const Graph& copy)=delete;
	Graph(istream& dataStream);
	string toString() const;
	void setEdge(unsigned int from,unsigned int to,bool connected);
	bool getEdge(unsigned int from,unsigned int to) const;

};

void testGraphConstruction(){
	//File presented in design document. Faked here to be a stream so we don't have to do file open checks and handling.

	stringstream fakeFile("3\n0 1 0\n1 0 1\n0 1 0");
	fakeFile.seekp(0);
	Graph g(fakeFile);
	cout<<g.toString()<<endl;
}
int main(int argc,char* argv[]){
	testGraphConstruction();
}

Graph::Graph(istream& dataStream){
	//read the number of vertecies in the graph.
	dataStream>>count;
	//create a unique_pointer.
	adjacency=make_unique<bool[]>(count*count);
	unsigned int state;
	for(int fromIdx=0;fromIdx<count;fromIdx++){
		for(int toIdx=0;toIdx<count;toIdx++){
			dataStream>>state;
			cout<<"Edge from  "<<fromIdx<<" to "<<toIdx<<" "<<state<<endl;
			if(state==1){
				setEdge(fromIdx,toIdx,true);
			}
		}
	}
}

string Graph::toString() const{
	stringstream out;
	for(int row=0;row<count;row++){
		for(int col=0;col<count-1;col++){
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

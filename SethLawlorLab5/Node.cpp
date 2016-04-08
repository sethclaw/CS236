#include "Node.h"

Node::Node() {}
Node::~Node(){}

void Node::insertNode(int i){
	adjacent_nodes.insert(i);
}
bool Node::getVisited(){
	return visited;
}
void Node::markVisit(){
	visited = true;
}
string Node::printNode(){
	stringstream out;
	for(auto Node: adjacent_nodes){
		out << " R" << Node; 
	}
	return out.str();
}
vector<int> Node::getNodes(){
	vector<int> temp_list;
	copy(adjacent_nodes.begin(), adjacent_nodes.end(), std::back_inserter(temp_list));
	return temp_list;
};
void Node::setPoNum(int poNum){
	postOrderNumber = poNum;
}
int Node::getPoNum(){
	return postOrderNumber;
}
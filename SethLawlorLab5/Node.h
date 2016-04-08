#pragma once
#ifndef NODE_H
#define NODE_H

#include <set>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class Node {
public:
	Node();
	~Node();
	void insertNode(int);
	string printNode();
	bool getVisited();
	vector<int> getNodes();
	void setPoNum(int);
	void markVisit();
	int getPoNum();
private:
	bool visited = false;
	int postOrderNumber;
	set<int> adjacent_nodes;
};

#endif
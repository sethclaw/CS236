#pragma once
#ifndef GRAPH_H
#define GRAPH_h

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include "Node.h"
#include "Rule.h"
using namespace std;

class Graph {
public:
    Graph ();
    Graph (vector<Rule>&);
    virtual ~Graph();

	map<int,set<int>> getSCCs();
	vector<int> getPO();
    bool dependent(int rule_index);
    string printDepGraph();
    string printRevDepGraph();
    string printPoNum();
    string printSearchOrder();
private:
	vector<Rule> Rules;
	map<int, Node> depGraph;
	map<int, Node> revDepGraph;
	void buildGraphs();
	void confirmNodes();
	void dfs(int);
	void dfsForest();
	int poNum = 1;
	map<int,set<int>> SCCs;
	void makeSCC();
	map<int, int> postOrder;
	vector<int> postOrderVector;
	void getPostOrder();
	void sccDFS(int,set<int>& sccomponent);
	
};

#endif
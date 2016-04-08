#pragma once
#ifndef RELATION_H
#define RELATION_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <assert.h>
#include "Scheme.h"
#include "Tuple.h"
//#include "Predicate.h"

using namespace std;
class Relation {
public:
	Relation(string);
	~Relation();
	
	string Name;
	Scheme schemes;
	set<Tuple> tuples;

	void select(vector<string>);
	void project(vector<string>);
	void reduce(vector<string>);
	void rename(vector<string>);
	void join(Relation import);
	vector<Tuple> unionWith(Relation& import);
	string print();
private:

	Scheme query_schemes;
	Scheme join_scheme;
	string printTup(Tuple);
	vector<vector<int>> join_pairs;
	vector<int> projectCols;
	vector<int> reduceCols;
	vector<int> uniquecols;
	set<Tuple> join_tuples;
	vector<Tuple> select(string,vector<int>&);
	vector<Tuple> select(vector<int>&);
	void projectScheme();
	void joinedSchema(Scheme& imported_schemes);
	vector<int> joinable(Tuple&,Tuple&);
	Tuple setJoin(Tuple&, Tuple&,  vector<int>&);
	Tuple setJoin(Tuple&, Tuple&);
	void setTuples(vector<Tuple>&);
	bool isConstant(string);
	vector<Tuple> setIntersect(vector<Tuple>& v1,vector<Tuple> v2);
};
#endif
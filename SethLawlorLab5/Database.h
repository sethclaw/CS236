#pragma once
#ifndef DATABASE_H
#define DATABASE_H
#include "Predicate.h"
#include "Scheme.h"
#include "Relation.h"
#include "Rule.h"
#include "Query.h"
#include "Tuple.h"
#include "Graph.h"
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Database {
public:
	Database();
	~Database();



	void populateDB(vector<Predicate>, vector<Predicate>, vector<Rule>, vector<Predicate>);
	void print(ofstream&);
private:
	vector<Predicate> Schemes;
	vector<Predicate> Facts;
	vector<Rule> Rules;
	vector<Predicate> Queries;
	map<string, Relation> Relations;
	void evalSchemes();
	void evalFacts();
	void evalGraphRules();
	void evalRules();
	void evalQueries();
	void printFacts();
	void printDiff(vector<string>&,vector<Tuple>&);
	void addScheme(Predicate&);
	void addFact(Predicate&);
	map<int,vector<int>> mapSet2Vector(map<int,set<int>>);
	void evalRule(int);
	void evalRule(vector<int>);
	stringstream output;
	stringstream debug;
	
};
#endif
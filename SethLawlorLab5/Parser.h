#pragma once
#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "Scanner.h"
#include "Predicate.h"
#include "Rule.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

class Parser{
public:
	Parser();
	Parser(vector<Token>);
	~Parser();
	//void Print();
	//void Print(ofstream&);
	void Parse();
	void print(ofstream&);
	vector<Predicate> getSchemes();
	vector<Predicate> getFacts();
	vector<Predicate> getQueries();
	vector<Rule> getRules();
private:
	vector<Token> myTokens;
	int i = 0; // Token index
	vector<Predicate> DSchemes;
	vector<Predicate> DFacts;
	vector<Predicate> DQueries;
	vector<Rule> DRules;
	set<string> Domain;
	set<string>::iterator iter;
	void Match(TokenType);
	
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	
	void scheme();
	void fact();
	void rule();
	void query();

	void predicateList();
	Predicate predicate();

	void parameterList();
	void parameter();
	bool success = true;
	Token badToken;

};

#endif
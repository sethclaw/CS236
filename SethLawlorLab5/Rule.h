#ifndef RULE_H
#define RULE_H

#include "Token.h"
#include "Predicate.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Rule {
public:
	Rule();
	~Rule();
	Rule(Predicate);
	Predicate getKey();
	void addValue(Predicate);
	vector<Predicate> getValues();
	string getRule();
private:
	Predicate key;
	vector<Predicate> values;
};

#endif
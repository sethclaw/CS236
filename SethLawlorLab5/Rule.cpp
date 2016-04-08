#include "Rule.h"

using namespace std;

Rule::Rule(){}
Rule::~Rule(){}

Rule::Rule(Predicate pred){
	key = pred;
}
void Rule::addValue(Predicate pred){
	values.push_back(pred);
}
Predicate Rule::getKey(){
	return key;
}
vector<Predicate> Rule::getValues(){
	return values;
}
string Rule::getRule(){
	stringstream out;
	out << key.getPredicate() << " :- ";
	for(unsigned i = 0; i < values.size(); i++){
		out << values[i].getPredicate();
		if(i+1 < values.size())
			out << ",";
	}
	return out.str();
}

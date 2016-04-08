#include "Predicate.h"
#include <iostream>
using namespace std;
Predicate::Predicate(){}

Predicate::~Predicate(){}

Predicate::Predicate(Token id_name){
	DID = id_name;
}

void Predicate::addParam(Token param){
	DParameters.push_back(param);
}
void Predicate::openPred(Token open_paren){
	Dopen = open_paren;
}
void Predicate::closePred(Token close_paren){
	Dclose = close_paren;
}
string Predicate::getName(){
	return DID.getValue();
}
string Predicate::getPredicate(){
	stringstream out;
	out << DID.getValue() << Dopen.getValue();
	for(unsigned i = 0; i < DParameters.size(); i++){
		out << DParameters[i].getValue();
	}
	out << Dclose.getValue();
	//cout << ".getPredicate() " << out.str() << endl;
	return out.str();
};
vector<string> Predicate::getParameters(){
	vector<string> Parameters;
	for(auto i: DParameters){
		if (i.getValue() != ",")
			Parameters.push_back(i.getValue());
	}
	return	Parameters;
};
//bool Predicate::validPredicate(){};
#ifndef PREDICATE_H
#define PREDICATE_H
#include "Parameter.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Predicate {
	public:
		Predicate();
		Predicate(Token);
		~Predicate();
		void addParam(Token);
		void openPred(Token);
		void closePred(Token);
		string getPredicate();
		string getName();
		vector<string> getParameters();
		//bool vaildPredicate();


	private:
		Token DID, Dopen, Dclose;
		vector<Parameter> DParameters;
		//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
};

#endif
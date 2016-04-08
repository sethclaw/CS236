#include "Parser.h"

using namespace std;

Parser::Parser(vector<Token> vec){
	myTokens = vec;
}
Parser::~Parser(){}

void Parser::Parse(){
	//try{	
		//Match(SCHEMES);
		schemeList();
		//Match(FACTS);
		factList();
		//Match(RULES);
		ruleList();
		//Match(QUERIES);
		queryList();
		Match(END);
		//throw myTokens[i];
	//}
	//catch(Token e){
	//	badToken = e;
	//	success = false;
	//}
}
void Parser::Match(TokenType t){
	if(t == myTokens[i].getType()){
		i++;
		if(t <= 3)//SCHEMES: 0, FACTS: 1, RULES: 2, QUERIES: 3
			Match(COLON);
		if(t == COMMA){
			if(myTokens[i].getType() != STRING && myTokens[i].getType() != ID)
				throw  myTokens[i];
		}
	}
	else
		throw  myTokens[i];
	
		
};
void Parser::schemeList(){
	Match(SCHEMES);
	scheme();

}

void Parser::factList(){
	Match(FACTS);
	fact();
}
void Parser::ruleList(){
	Match(RULES);
	rule();
}
void Parser::queryList(){
	Match(QUERIES);
	query();
}

void Parser::scheme(){
	while(myTokens[i].getType() == ID)
		DSchemes.push_back(predicate());
	if(myTokens[i].getType() == FACTS && DSchemes.size() > 0)
		return;//parse();
	else
		throw myTokens[i];
}
void Parser::fact(){
	while(myTokens[i].getType() == ID){
		DFacts.push_back(predicate());
		Match(PERIOD);
	}
	if(myTokens[i].getType() == RULES)
		return;
	else
		throw myTokens[i];
}
void Parser::rule(){
	if(myTokens[i].getType() == ID){
		Rule newrule(predicate());
		Match(COLON_DASH);
		if(myTokens[i].getType() != ID)
			throw myTokens[i];
		while(myTokens[i].getType() == ID){
			newrule.addValue(predicate());
			if(myTokens[i].getType() == COMMA)
				Match(COMMA);
			else 
				break;
		}
		Match(PERIOD);
		DRules.push_back(newrule);
		rule();
	}
	else if(myTokens[i].getType() == QUERIES)
		return;
	else
		throw myTokens[i];
	
}
void Parser::query(){
	while(myTokens[i].getType() == ID){
		DQueries.push_back(predicate());
		Match(Q_MARK);
	}
	if(DQueries.size() > 0)
		return;
	else
		throw myTokens[i];
}

void Parser::predicateList(){

}
Predicate Parser::predicate(){
	Predicate newpred(myTokens[i]);//should already be check to be ID
	Match(ID);
	newpred.openPred(myTokens[i]);//should be "("
	Match(LEFT_PAREN);
	if(myTokens[i].getType() != STRING && myTokens[i].getType() != ID)
		throw	myTokens[i];
	newpred.addParam(myTokens[i]);//adds first Parameter
	Match(myTokens[i].getType());// should be ID or String 
	while(myTokens[i].getType() != RIGHT_PAREN){
		newpred.addParam(myTokens[i]);
		Match(COMMA); //which now checks for following ID or String 
		newpred.addParam(myTokens[i]);
		if(myTokens[i].getType() == STRING)
			Domain.insert(myTokens[i].getValue());
		Match(myTokens[i].getType());//will be either string or ID
	}
	newpred.closePred(myTokens[i]);
	Match(RIGHT_PAREN);
	//ending will be matched in specific parse
	return newpred;
}


void Parser::parameterList(){

}
void Parser::parameter(){

}

void Parser::print(ofstream& output){
	stringstream out;
	
	if (!success){
		out << "Failure!" << "\n  " <<   badToken.getInfo() << endl;
		cout << out.str();
		output << out.str();
		return;
	}
	
	out << "Success!" << endl;
	out << "Schemes(" << DSchemes.size() << "):" <<  endl;
	for(unsigned i = 0; i < DSchemes.size(); i++){
		out << "  " << DSchemes[i].getPredicate() << endl;
	}
	out << "Facts(" <<  DFacts.size() << "):" << endl;
	for(unsigned i = 0; i < DFacts.size(); i++){
		out << "  " << DFacts[i].getPredicate() << endl;
	}
	out << "Rules(" <<  DRules.size() << "):" << endl;
	for(unsigned i = 0; i < DRules.size(); i++){
		out << "  " << DRules[i].getRule() << endl;
	}
	out << "Queries(" <<  DQueries.size() << "):" << endl;
	for(unsigned i = 0; i < DQueries.size(); i++){
		out << "  " << DQueries[i].getPredicate() << endl;
	}
	out << "Domain(" <<  Domain.size() << "):" << endl;
	for(iter=Domain.begin(); iter!=Domain.end();++iter){
		out << "  " << *iter  << endl;
	}
	cout << out.str();
	output << out.str();
};
vector<Predicate> Parser::getSchemes(){
	return DSchemes;
};
vector<Predicate> Parser::getFacts(){
	return DFacts;
};
vector<Predicate> Parser::getQueries(){
	return DQueries;
};
vector<Rule> Parser::getRules(){
	return DRules;
};
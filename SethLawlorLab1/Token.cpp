#include "Token.h"
#include <iostream>
#include <sstream>

Token::Token(){}
Token::~Token(){}

Token::Token(TokenType t_type, string t_value, int line_num){
	TType = t_type;
	TValue = t_value;
	LineNum = line_num;
	}

TokenType Token::getType(){
	return TType;	
	}

string Token::getValue(){
	return TValue;
	}

int Token::getLine(){
	return LineNum;
	}

string Token::getInfo(){
	stringstream ss;
	if(TType == ERROR)
		ss << TokenTypeToString(TType) << LineNum << endl;
	else if(TType == END){
		ss << "(" << TokenTypeToString(TType) << ",\"";
		ss << "" << "\",";
		ss << LineNum <<")" << endl;
		ss << "Total Tokens = " << TValue; // if end of file then TValue should equal the total number of tokens
	}else{
		ss << "(" << TokenTypeToString(TType) << ",\"";
		ss << TValue << "\",";
		ss << LineNum <<")";

	}
	return ss.str();
	};

string Token::TokenTypeToString(TokenType tt){
	string out;
	switch(tt){
		case COMMA:
			out = "COMMA";
			break;
		case PERIOD:
			out = "PERIOD";
			break;
		case Q_MARK:
			out = "Q_MARK";
			break;
		case LEFT_PAREN:
			out = "LEFT_PAREN";
			break;
		case RIGHT_PAREN:
			out = "RIGHT_PAREN";
			break;
		case COLON:
			out = "COLON";
			break;
		case COLON_DASH:
			out = "COLON_DASH";
			break;
		case SCHEMES:
			out = "SCHEMES";
			break;
		case FACTS:
			out = "FACTS";
			break;
		case RULES:
			out = "RULES";
			break;
		case QUERIES:
			out = "QUERIES";
			break;
		case ID:
			out = "ID";
			break;
		case STRING:
			out = "STRING";
			break;
		case ERROR:
			out = "Input Error on line ";
			break;
		case END:
			out = "EOF";
	}
	return out;
}
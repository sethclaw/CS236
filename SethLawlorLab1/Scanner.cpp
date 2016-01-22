#include "Scanner.h"
#include "Token.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

Scanner::Scanner(){}
Scanner::~Scanner(){}

void Scanner::Scan(ifstream & file){
	//file = toRead; 
	char c;
	errors = false;
	while(!file.eof() && errors == false){
		
		 c = file.get();

		switch(c){
			case EOF:
				//cout << "thats the end of the movie";
				myTokens.push_back(Token(END,to_string(myTokens.size() + 1),Line));
				break;
			case ',':
				myTokens.push_back(Token(COMMA,toString(c),Line));
				break;
			case '.':
				myTokens.push_back(Token(PERIOD,toString(c),Line));
				break;
			case '(':
				myTokens.push_back(Token(LEFT_PAREN,toString(c),Line));
				break;
			case ')':
				myTokens.push_back(Token(RIGHT_PAREN,toString(c),Line));
				break;
			case '?':
				myTokens.push_back(Token(Q_MARK,toString(c),Line));
				break;
			case '\n':
				Line++;
				break;
			case '#': //comments
				while(file.peek() != '\n')
					c = file.get();
				cout << endl;
				break;
			case ':':
				if (file.peek() == '-'){
					file.get(); //COLON_DASH
					myTokens.push_back(Token(COLON_DASH,":-",Line));
				}else{
					myTokens.push_back(Token(COLON,toString(c),Line));
				}
				break;
			case '\'':{
				string out;
				out += c; 
				out += ScanString(file);
				if (!vaildString(out)){
					myTokens.push_back(Token(ERROR,toString(c),Line));
					errors = true;
				} else
					myTokens.push_back(Token(STRING,out,Line));
				break;
			}
			default://is ID?
			if(!isspace(c))
				 errors = ScanId(c,file);
		}
	}
}

bool Scanner::vaildString(string my_string){
	if (my_string.back() == '\n' || my_string.back() == EOF)
		return false;
	else 
		return true;
}

string Scanner::toString(char character){
	string myString = "";
	myString += character;
	return myString;
}

string Scanner::ScanString(ifstream& file){
	string LitString;
	char c = file.get();
	while(c != '\'' && c != '\n' && c != EOF){
		LitString += c;
		c = file.get();
	}
	LitString += c;// discard end-quote
	return LitString;
}

bool Scanner::ScanId(char d,ifstream& file){
	char c = d;
	string out; 
	// ID
	if(isalpha(c)){
		while(isalnum(c)){
			out += c;
			if(isalnum(file.peek()))
				c = file.get();
			else
				break;
		}
		if(out == "Schemes")
			myTokens.push_back(Token(SCHEMES,out,Line));
		else if(out == "Facts")
			myTokens.push_back(Token(FACTS,out,Line));
		else if(out == "Rules")
			myTokens.push_back(Token(RULES,out,Line));
		else if(out == "Queries")
			myTokens.push_back(Token(QUERIES,out,Line));
		else //is ID
			myTokens.push_back(Token(ID,out,Line));
		return false;
	}
	else
		myTokens.push_back(Token(ERROR,toString(c),Line)); return true;
};

void Scanner::print(ofstream& output){
	for(unsigned i = 0; i < myTokens.size(); i++){
		cout << myTokens[i].getInfo() << endl;
	}
	for(unsigned i = 0; i < myTokens.size(); i++){
		output << myTokens[i].getInfo() << endl;
	}
}
#ifndef SCANNER_H
#define SCANNER_H
#include "Token.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

using namespace std;

class Scanner{
public:
		Scanner();
		~Scanner();
		void Scan(ifstream&);
		void print(ofstream&);
		vector<Token> getVector();
private:
	vector<Token> myTokens;
	bool errors;
	string toString(char);
	bool ScanId(char,ifstream&);
	string ScanString(ifstream&);
	bool vaildString(string);
	// int c;
	int Line = 1;
};

#endif

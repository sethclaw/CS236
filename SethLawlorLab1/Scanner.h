#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include "Token.h"
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class Scanner{
public:
		Scanner();
		~Scanner();
		void Scan(ifstream&);
		void print(ofstream&);
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

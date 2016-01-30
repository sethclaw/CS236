#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum TokenType {
		SCHEMES,//0
		FACTS,//1
		RULES,//2
		QUERIES,//3
		COLON,
		PERIOD,
		Q_MARK,
		LEFT_PAREN,
		RIGHT_PAREN,
		COMMA,
		COLON_DASH,
		ID,
		STRING,
		ERROR,
		END
	};

class Token {
	public:
		Token();
		Token(TokenType, string, int);
		~Token();
		TokenType getType();
		string getValue();
		int getLine();
		string getInfo();
	private:
		TokenType TType;
		string TValue;
		int LineNum;
		string TokenTypeToString(TokenType tt);

};

#endif
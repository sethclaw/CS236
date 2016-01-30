#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum TokenType {
		COMMA,
		PERIOD,
		Q_MARK,
		LEFT_PAREN,
		RIGHT_PAREN,
		COLON,
		COLON_DASH,
		SCHEMES,
		FACTS,
		RULES,
		QUERIES,
		ID,
		STRING,
		ERROR,
		END
	};

class Token {
	public:
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
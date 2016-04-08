#pragma once
#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
#include "Token.h"
using namespace std;

class Parameter {
public:
	Parameter(Token);
	~Parameter();
	string getValue();
private:
	Token ParamToken;
};

#endif
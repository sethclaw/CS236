#include "Parameter.h"
using namespace std;

Parameter::Parameter(Token t){
	ParamToken = t;
}
Parameter::~Parameter(){}

string  Parameter::getValue(){
	return ParamToken.getValue();
};
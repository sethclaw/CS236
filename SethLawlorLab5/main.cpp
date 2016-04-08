#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Database.h"
#include "Token.h"
#include "Rule.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
	
	ifstream file2read;
	ofstream file2write;

	file2read.open(argv[1]);
	file2write.open(argv[2]);

	Scanner scan;
	scan.Scan(file2read);
	file2read.close();
	//cout << "Datalog Scanner + Parser" << endl;
	//scan.print(file2write);
	/* NOW were parsin'!*/
	Parser parse(scan.getVector());
	try{
	
	parse.Parse();
	//parse.print(file2write);

	}
	catch(Token e){
		cout << "catch!" << "Type: " << e.getType() << " Value: " << e.getValue() << " Line: " << e.getLine() << endl;

	}
	Database myDatabase;
	vector<Predicate> mySchemes = parse.getSchemes();
	vector<Predicate> myFacts = parse.getFacts();
	vector<Rule> myRules = parse.getRules();
	vector<Predicate> myQueries = parse.getQueries();
	myDatabase.populateDB(mySchemes, myFacts, myRules, myQueries);
	myDatabase.print(file2write);
	file2write.close();
	cout << endl;
	return 0;
}
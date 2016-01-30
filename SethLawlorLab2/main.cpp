#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
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
	cout << "Datalog Scanner + Parser" << endl;
	scan.print(file2write);
	/* NOW were parsin'!*/
	Parser parse(scan.getVector());
	parse.Parse();
	file2read.close();
	file2write.close();
	cout << endl;
	return 0;
}
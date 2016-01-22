#include "Token.h"
#include "Scanner.h"
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
	cout << "###################################################################"<< endl;
	cout << "#                                                                 #"<< endl;
	cout << "#                          DATA LOG SCANNER                       #"<< endl;
	cout << "#                          by Seth Lawlor jan 2016                #"<< endl;
	cout << "###################################################################"<< endl << endl;
	scan.print(file2write);
	file2read.close();
	file2write.close();
	cout << endl;
	return 0;
}
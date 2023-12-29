#include <fstream>
#include <iostream> //hello
#include <regex>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "MultiStatementRegex.h"
#include "SingleStatementRegex.h"
#include "Tokenization.h"
#include "ThreeAddressCode.h"
#include "Tokenization.h"
#include "StatementEvaluation.h"
using namespace std;

string input_file = "code.txt";
string output_file = "output.txt";

int main() {
	char choice;
	cout << "\t\t\t\t\tCOMPILER CONSTRUCTION" << endl;
	cout << "\n\t\t\t1.Tokenize" << endl;
	cout << "\n\t\t\t2.Single Statement Regex" << endl;
	cout << "\n\t\t\t3.Multi-Statement Regex" << endl;
	cout << "\n\t\t\t4.Three Address Code" << endl;
	cout << "\n\t\t\tEnter your choice: ";
	cin >> choice;
	if (choice == '1') {
		tokenize(input_file);
	}
	else if (choice == '2') {
		singleLineRegularExpression(input_file);
	}
	else if (choice == '3') {
		multiLineRegularExpression(input_file);
	}
	else if (choice == '4') {
		threeAddressCode(input_file, output_file);
	}
	else if (choice == '5') {
		StatementEvaluation(input_file);
	}
	else {
		cout << "Invalid choice" << endl;
	}
}
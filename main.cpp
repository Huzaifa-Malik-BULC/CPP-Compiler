#include <fstream>
#include <iostream>
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
#include "SymbolTable.h"
#include "RecursiveParsing.h"
#include "SyntaxAnalysis.h";
#include "SyntaxAnalysis&TreeExpression.h";
using namespace std;

string input_file = "code.txt";
string output_file = "output.txt";

int main() {
	char choice;
	cout << "\t\t\t\t\tCOMPILER CONSTRUCTION" << endl;
	cout << "\n\t\t\t1. Tokenize" << endl;
	cout << "\n\t\t\t2. Single Statement Regex" << endl;
	cout << "\n\t\t\t3. Multi-Statement Regex" << endl;
	cout << "\n\t\t\t4. Three Address Code" << endl;
	cout << "\n\t\t\t5. Statement Evaluation" << endl;
	cout << "\n\t\t\t6. Symbol Table" << endl;
	cout << "\n\t\t\t7. Recursive Parsing" << endl;
	cout << "\n\t\t\t8. Syntax Analysis" << endl;
	cout << "\n\t\t\t9. Syntax Analysis and Tree Expression" << endl;
	cout << "\n\t\t\t0. Exit" << endl;
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
	else if (choice == '6') {
		SymbolTable(input_file);
	}
	else if (choice == '7') {
		RecursiveParse(input_file);
	}
	else if (choice == '8') {
		Syntaxanalysis(input_file);
	}
	else if (choice == '9') {
		syntaxAnalysisAndTreeExpression(input_file);
	}
	else {
		exit(0);
	}
}
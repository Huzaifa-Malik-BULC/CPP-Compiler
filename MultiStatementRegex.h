#pragma once
#include<iostream>
#include<fstream>
#include<regex>
#include<string>
using namespace std;

void multiLineRegularExpression(string input_file) {
	ifstream file(input_file);

	string code = "";
	 
	regex regex_assignment("^\\s*\\w+\\s*\\=\\s*((\"[ \\w]*\")|(\\d+(.\\d+)?))([\\+\\-\\*\\/]((\"[ \\w]*\")|(\\s*\\d+(.\\d+)?\\s*)))?\\s*;\\s*$");
	regex regex_conditional_jump("^\\s*if\\s*\\(\\s*\\w+\\s*(\\=\\=|\\>\\=|\\<\\=)\\s*\\w\\s*\\)\\s*\\{?\\s*goto\\s+\\w+\\s*;\\s*\\}?\\s*$");
	regex regex_procedure("^\\s*\\w+\\s*\\(((\\s*\\w*\\s*)|((\\s*\\w+\\s*)(\\s*\\,\\s*\\w+\\s*)+))\\)\\s*;\\s*$");
	regex regex_copy("^\\s*[A-Za-z_]+\\w*\\s*\\=\\s*[A-Za-z_]+\\w*\\s*;\\s*$");
	regex regex_unconditonal_jump("^\\s*goto\\s+[A-Za-z_]\\w*\\s*;\\s*$");

	regex regex_for("^for\\s*\\(\\s*[a-zA-Z_]\\w*\\s*=\\s*\\w+\\s*;\\s*[a-zA-Z_]\\w*\\s*(<|<=|>|>=|==|!=)\\s*\\w+\\s*;\\s*[a-zA-Z_]\\w*\\s*[-+]\\s*[-+]?\\d*\\s*\\)\\s*\\{\\s*[A-Za-z_]+\\w*\\s*\\=\\s*[A-Za-z_]+\\w*\\s*;\\s*\\}\\s*;?$");
	regex regex_while("^\\s*while\\s*\\(\\s*[A-Za-z_]\\w*\\s*(==|<|>|>=|<=)\\s*((\\d+)|([A-Za-z_]\\w*))\\s*\\)\\s*\\{\\s*\\}\\s*$");
	regex regex_do_while("^\\s*do\\s*\\s*\\{\\s*\\}\\s*while\\s*\\(\\s*[A-Za-z_]\\w*\\s*(==|<|>|>=|<=)\\s*((\\d+)|([A-Za-z_]\\w*))\\s*\\)\\s*;\\s*$");

	regex regex_function("^(int|double|string|float|bool|void)\\s+\\w+\\((((int|double|string|float|bool|void)\\s+\\w*)|((int|double|string|float|bool|void)\\s+\\w*(\\,\\s*(int|double|string|float|bool|void)\\s+\\w*)*))\\);$");
	regex regex_switch("^\\s*switch\\s*\\(\\s*[A-Za-z_]\\w*\\s*\\)\\s*\\{\\s*(case\\s*((\\'[A-Za-z]\\')|([0-9]+))\\s*\\:\\s*(.)*\\s*(break;\\s*)?(\\s*default\\s*\\:\\s*(.)*(break;)?)?)*\\}$");
	regex regex_array("^\\s*(int|string|double|float|char)\\s+[A-Za-z_]\\w*\\s*(\\s*\\[\\s*\\d+\\s*\\]\\s*)+\\s*;\\s*$");
	regex regex_pointer("^\\s*(int|float|double|char)\\s*\\*\\s*[A-Za-z_]\\w*\\s*;$");


	if (file.is_open()) {
		char ch;
		while (!file.eof()) {
			file.get(ch);
			if (ch == '$') {
				if (regex_match(code, regex_assignment)) {
					cout << "Valid Assignment Expression" << endl;
				}
				else if (regex_match(code, regex_conditional_jump)) {
					cout << "Valid Conditional Statment" << endl;
				}
				else if (regex_match(code, regex_procedure)) {
					cout << "Valid Procedure Call" << endl;
				}
				else if (regex_match(code, regex_copy)) {
					cout << "Valid Copy Statment" << endl;
				}
				else if (regex_match(code, regex_unconditonal_jump)) {
					cout << "Valid Unconditional Statment" << endl;
				}
				else if (regex_match(code, regex_for)) {
					cout << "Valid For Loop" << endl;
				}
				else if (regex_match(code, regex_while)) {
					cout << "Valid While Loop" << endl;
				}
				else if (regex_match(code, regex_do_while)) {
					cout << "Valid Do While Loop" << endl;
				}
				else if (regex_match(code, regex_switch)) {
					cout << "Valid Switch Statment" << endl;
				}
				else if (regex_match(code, regex_function)) {
					cout << "Valid Function Declaration" << endl;
				}
				else if (regex_match(code, regex_array)) {
					cout << "Valid Array Declaration" << endl;
				}
				else if (regex_match(code, regex_pointer)) {
					cout << "Valid Pointer Declaration" << endl;
				}
				else {
					cout << "Syntax Error" << endl;
				}

				code = "";
			}
			else {
				code += ch;
			}
		}
	}
}
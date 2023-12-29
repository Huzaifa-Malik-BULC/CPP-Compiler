#pragma once
#include<iostream>
#include<fstream>
#include<regex>
using namespace std;

fstream file;

void if_else_body();
void do_while_body();
void lex(char);
bool check_for_statements(string line);



void lex(char c) {
	char ch;

	if (c == 'd') {
		if (file.eof()) {
			return;
		}
		file.get(ch);
		if (ch == 'o') {
			do_while_body();
		}
		else {
			cerr << "Syntax Error 1";
			exit(1);
		}
	}
	else if (c == 'i') {
		if (file.eof()) {
			return;
		}
		file.get(ch);
		if (ch == 'f') {
			if_else_body();
		}
		else {
			cerr << "Syntax Error 2";
			exit(1);
		}
	}
}

bool check_for_statements(string line) {
	regex assignment("^\\s*\\w+\\s*\\=\\s*((\"[ \\w]*\")|(\\d+(.\\d+)?))([\\+\\-\\*\\/]((\"[ \\w]*\")|(\\s*\\d+(.\\d+)?\\s*)))?\\s*;\\s*$");
	regex copy("^\\s*[A-Za-z_]+\\w*\\s*\\=\\s*[A-Za-z_]+\\w*\\s*;\\s*$");
	regex _array("^\\s*(int|string|double|float|char)\\s+[A-Za-z_]\\w*\\s*(\\s*\\[\\s*\\d+\\s*\\]\\s*)+\\s*;\\s*$");
	regex pointer("^\\s*(int|float|double|char)\\s*\\*\\s*[A-Za-z_]\\w*\\s*;$");
	regex condition("^\\s*\\w+\\s*(\\=\\=|\\<|\\>|\\<\\=|\\>\\=)\\s*((\"[ \\w]*\")|(\\d+(.\\d+)?))([\\+\\-\\*\\/]((\"[ \\w]*\")|(\\s*\\d+(.\\d+)?\\s*)))?\\s*$");

	// i==0

	if (
		regex_match(line, assignment) ||
		regex_match(line, copy) ||
		regex_match(line, _array) ||
		regex_match(line, pointer) || regex_match(line, condition)
		)
	{
		return true;
	}
	else return false;
}

void if_else_body() {
	char ch;
	string statement = "";
	file.get(ch);
	if (ch == '(') {
		file.get(ch);
		statement += ch;
		while (ch != ')' && !file.eof()) {
			file.get(ch);
			statement += ch;
			while (ch != ')' && !file.eof()) {
				file.get(ch);
				statement += ch;
			}
			statement.pop_back();
			if (check_for_statements(statement)) {
				statement = "";
			}
			else {
				cerr << "Syntax Error 17";
				exit(1);
			}
		}
		file.get(ch);
		while (ch == '\n' || ch == ' ' || ch == '\t') {
			file.get(ch);
		}
		if (ch == '{') {
			while (ch != '}' && !file.eof()) {
				file.get(ch);
				if (ch == ';') {
					statement += ch;
					;					if (!check_for_statements(statement)) {
						cerr << "Syntax Error 121";
						exit(1);
					}
					statement = "";
				}
				else if (ch != '\n' && ch != ' ' && ch != '\t') {
					statement += ch;
				}
			}
			if (ch == '}') {
				file.get(ch);
				while (ch != ' ' && ch != '\t' && ch != '\n') {
					file.get(ch);
				}
				if (ch == 'e') {
					file.get(ch);
					if (ch == 'l') {
						file.get(ch);
						if (ch == 's') {
							file.get(ch);
							if (ch == 'e') {
								file.get(ch);
								while (ch != '{' && !file.eof())
									if (ch == '{') {
										while (ch != '}' && !file.eof()) {
											file.get(ch);
											if (ch == ';') {
												statement += ch;
												if (!check_for_statements(statement)) {
													cerr << "Syntax Error 121";
													exit(1);
												}
												statement = "";
											}
											else if (ch != '\n' && ch != ' ' && ch != '\t') {
												statement += ch;
											}
										}
										if (ch == '}') {
											cout << "Valid IF Statement\n";
											return;
										}
									}
									else {
										cerr << "Syntax Error 304";
										exit(1);
									}
							}
							else {
								cerr << "Syntax Error 301";
								exit(1);
							}
						}
						else {
							cerr << "Syntax Error 302";
							exit(1);
						}
					}
					else {
						cerr << "Syntax Error 303";
						exit(1);
					}
				}
				else {
					file.unget();
					cout << "Valid IF ELSE Statement\n";
					return;
				}
			}
			else {
				cerr << "Syntax Error 3";
				exit(1);
			}
		}
		else {
			cerr << "Syntax Error 4";
			exit(1);
		}
	}
	else {
		cerr << "Syntax Error 6";
		exit(1);
	}
}

void do_while_body() {
	char ch;
	string helping_string = "";
	file.get(ch);
	if (ch == '{') {
		while (ch != '}' && !file.eof()) {
			file.get(ch);
			if (ch == ';') {
				helping_string += ch;
				if (!check_for_statements(helping_string)) {
					cerr << "Syntax Error 121";
					exit(1);
				}
				helping_string = "";
			}
			else if (ch != '\n' && ch != ' ' && ch != '\t') {
				helping_string += ch;
			}
		}
		helping_string = "";
		if (ch == '}') {
			file.get(ch);
			if (ch == 'w') {
				file.get(ch);
				if (ch == 'h') {
					file.get(ch);
					if (ch == 'i') {
						file.get(ch);
						if (ch == 'l') {
							file.get(ch);
							if (ch == 'e') {
								file.get(ch);
								if (ch == '(') {
									while (ch != ')' && !file.eof()) {
										file.get(ch);
										helping_string += ch;
									}
									helping_string.pop_back();
									if (!check_for_statements(helping_string)) {
										cerr << "Invalid Do While Syntax\n";
										exit(1);
									}
									if (ch == ')') {
										file.get(ch);
										if (ch == ';') {
											cout << "Valid DO While Statement\n";
											return;
										}
										else {
											cerr << "Syntax Error 7";
											exit(1);
										}
									}
									else {
										cerr << "Syntax Error 8";
										exit(1);
									}
								}
								else {
									cerr << "Syntax Error 9";
									exit(1);
								}
							}
							else {
								cerr << "Syntax Error 10";
								exit(1);
							}
						}
						else {
							cerr << "Syntax Error 11";
							exit(1);
						}
					}
					else {
						cerr << "Syntax Error 12";
						exit(1);
					}
				}
				else {
					cerr << "Syntax Error 13";
					exit(1);
				}
			}
			else {
				cerr << "Syntax Error 14";
				exit(1);
			}
		}
		else {
			cerr << "Syntax Error 15";
			exit(1);
		}
	}
	else {
		cerr << "Syntax Error 16";
		exit(1);
	}
}


void Syntaxanalysis(string input_file) {
	char ch;

	file.open(input_file);
	if (file.is_open()) {
		while (!file.eof()) {
			file.get(ch);
			lex(ch);
		}
	}
}


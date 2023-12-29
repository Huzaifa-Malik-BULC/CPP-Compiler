#pragma once
#include<fstream>
#include<iostream>
using namespace std;

string helping_string = "";
bool is_keyword(string s) {
	vector<string> keywords = { "auto", "break", "case", "char", "const", "continue", "default", "do",
			"double", "else", "enum", "extern", "float", "for", "goto", "if",
			"int", "long", "register", "return", "short", "signed", "sizeof", "static",
			"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "main", "cout", "cin",
			"endl", "include", "namespace", "fstream", "using", "std", "string", "bool", "true", "false", "return",
			"istream", "ostream", "ifstream", "ofstream"
	};
	for (int i = 0; i < keywords.size(); i++) {
		if (s == keywords[i]) {
			return true;
		}
	}
	return false;
}

bool is_identifier(string s) {
	if (isalpha(s[0])) {
		for (size_t i = 1; i < s.length(); i++) {
			if (!isalpha(s[i]) && !isdigit(s[i] && s[i] != '_')) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool is_digit(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

namespace cn {
	typedef enum {
		UNDEFINED = 0, SPACE = 1, TAB, NEWLINE, DO, FOR, LEFT_PARANTHESIS, RIGHT_PARANTHESIS, COMMA, SEMICOLON, LEFT_BRACKET, RIGHT_BRACKET, MINUS,
		PLUS, INCREMENT, DECREMENT, EQUAL, DOUBLE_EQUAL, GREATER_THAN_EQUAL, LESS_THAN_EQUAL, PLUS_EQUAL, MINUS_EQUAL, MULTIPLY_EQUAL, DIVIDE_EQUAL, LESS_THAN,
		GREATER_THAN, DIVIDE, MULTIPLY, OUTPUT_STREAM, INPUT_STREAM, KEYWORD, IDENTIFIER, DIGIT, END_OF_LINE, SINGLE_LINE_COMMENT, MULTI_LINE_COMMENT

	} tokenType;
}
using namespace cn;
bool print = true;
class Token {
public:
	tokenType tt;
	string entryOne;
	int num;
	string variable;
	bool moveBack = false;

	static Token Lexical_Analyzer(char, ifstream&);
};

static void tokenize(string input_file) {
	system("cls");
	Token t;
	char ch;

	ifstream file(input_file);
	if (file.is_open()) {
		while (!file.eof()) {
			if (t.moveBack) {
				file.unget();
				t.moveBack = false;
			}
			file.get(ch);
			t = Token::Lexical_Analyzer(ch, file);
			if (print || file.eof()) {
				if (helping_string != "") {
					if (is_keyword(helping_string)) {
						cout << cn::KEYWORD << "\t" << "KEYWORD" << endl;
					}
					else if (is_identifier(helping_string)) {
						cout << cn::IDENTIFIER << "\t" << "IDENTIFIER" << endl;
					}
					else if (is_digit(helping_string)) {
						cout << cn::DIGIT << "\t" << "DIGIT" << endl;
					}
					else {
						cout << "UNDEFINED" << "\t" << helping_string << endl;
					}
					helping_string = "";
				}
				if (!file.eof()) {
					cout << t.tt << "\t" << t.entryOne << endl;
				}
			}
		}
	}
}

Token Token::Lexical_Analyzer(char c, ifstream& file) {
	Token t;

	if (c == ' ') {
		t.tt = tokenType::SPACE;
		t.entryOne = "SPACE";
		print = true;
		return t;
	}
	else if (c == '\t') {
		t.tt = tokenType::TAB;
		t.entryOne = "TAB";
		print = true;
		return t;
	}
	else if (c == '\n') {
		t.tt = tokenType::NEWLINE;
		t.entryOne = "NEWLINE";
		print = true;
		return t;
	}
	else if (c == '(') {
		t.tt = tokenType::LEFT_PARANTHESIS;
		t.entryOne = "LEFT PARENTHESIS";
		print = true;
		return t;
	}
	else if (c == ')') {
		t.tt = tokenType::RIGHT_PARANTHESIS;
		t.entryOne = "RIGHT PARENTHESIS";
		print = true;
		return t;
	}
	else if (c == '{') {
		t.tt = tokenType::LEFT_BRACKET;
		t.entryOne = "LEFT BRACKET";
		print = true;
		return t;
	}
	else if (c == '}') {
		t.tt = tokenType::RIGHT_BRACKET;
		t.entryOne = "RIGHT BRACKET";
		print = true;
		return t;
	}
	else if (c == ',') {
		t.tt = tokenType::COMMA;
		t.entryOne = "COMMA";
		print = true;
		return t;
	}
	else if (c == '+') {
		char temp;
		file.get(temp);
		if (temp == '+') {
			t.tt = tokenType::INCREMENT;
			t.entryOne = "INCREMENT";
			print = true;
			print = true;
			return t;
		}
		else if (temp == '=') {
			t.tt = tokenType::PLUS_EQUAL;
			t.entryOne = "PLUS EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = tokenType::PLUS;
			t.entryOne = "PLUS";
			print = true;
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '-') {
		char temp;
		file.get(temp);
		if (temp == '-') {
			t.tt = tokenType::DECREMENT;
			t.entryOne = "DECREMENT";
			print = true;
			return t;
		}
		else if (temp == '=') {
			t.tt = tokenType::MINUS_EQUAL;
			t.entryOne = "MINUS EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = tokenType::MINUS;
			print = true;
			t.entryOne = "MINUS";
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '<') {
		char temp;
		file.get(temp);
		if (temp == '=') {
			t.tt = tokenType::LESS_THAN_EQUAL;
			t.entryOne = "LESS THAN EQUAL";
			print = true;
			return t;
		}
		else if (temp == '<') {
			t.tt = tokenType::OUTPUT_STREAM;
			t.entryOne = "OUTPUT STREAM";
			print = true;
			return t;
		}
		else {
			t.tt = tokenType::LESS_THAN;
			t.entryOne = "LESS THAN";
			print = true;
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '>') {
		char temp;
		file.get(temp);
		if (temp == '=') {
			t.tt = tokenType::GREATER_THAN_EQUAL;
			t.entryOne = "GREATER THAN EQUAL";
			print = true;
			return t;
		}
		else if (temp == '>') {
			t.tt = tokenType::INPUT_STREAM;
			t.entryOne = "INPUT STREAM";
			print = true;
			return t;
		}
		else {
			t.tt = tokenType::GREATER_THAN;
			t.entryOne = "GREATER THAN";
			print = true;
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '/') {
		char temp;
		file.get(temp);
		if (temp == '=') {
			t.tt = tokenType::DIVIDE_EQUAL;
			t.entryOne = "DIVIDE EQUAL";
			print = true;
			return t;
		}
		else if (temp == '/') {
			t.tt = tokenType::SINGLE_LINE_COMMENT;
			t.entryOne = "SINGLE LINE COMMENT";
			while (temp != '\n') {
				file.get(temp);
				t.moveBack = true;
			}
			print = true;
			return t;
		}
		else if (temp == '*') {
			t.tt = tokenType::MULTI_LINE_COMMENT;
			t.entryOne = "MULTI LINE COMMENT";
			while (temp != '\n') {
				file.get(temp);
				if (temp == '*') {
					file.get(temp);
					if (temp == '/') {
						t.moveBack = true;
						break;
					}
				}
			}
			print = true;
			return t;
		}
		else {
			t.tt = tokenType::DIVIDE;
			t.entryOne = "DIVIDE";
			print = true;
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '*') {
		char temp;
		file.get(temp);
		if (c == '=') {
			t.tt = tokenType::MULTIPLY_EQUAL;
			t.entryOne = "MULTIPLY EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = tokenType::MULTIPLY;
			t.entryOne = "MULTIPLY";
			print = true;
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '=') {
		char temp;
		file.get(temp);
		if (temp == '=') {
			t.tt = tokenType::DOUBLE_EQUAL;
			print = true;
			t.entryOne = "DOUBLE EQUAL";
			return t;
		}
		else {
			t.tt = tokenType::EQUAL;
			print = true;
			t.entryOne = "EQUAL";
			t.moveBack = true;
			return t;
		}
	}
	else if (c == ';') {
		t.tt = tokenType::SEMICOLON;
		print = true;
		t.entryOne = "SEMICOLON";
		return t;
	}
	else if (c == '$') {
		t.tt = tokenType::END_OF_LINE;
		print = true;
		t.entryOne = "END_OF_LINE";
		return t;
	}
	else {
		helping_string += c;
		print = false;
		t.tt = tokenType::UNDEFINED;
		t.entryOne = "UNDEFINED";
		return t;
	}
}
#pragma once
#include<fstream>
#include<iostream>
using namespace std;

string helping_string = "";
bool is_keyword(string s) {
	vector<string> keywords = { "auto", "break", "case", "char", "const", "continue", "default", "do",
			"double", "else", "enum", "extern", "float", "for", "goto", "if",
			"int", "long", "register", "return", "short", "signed", "sizeof", "static",
			"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "main", "cout", "cin"
		, "endl", "include", "namespace"
	};
	for (int i = 0; i < 32; i++) {
		if (s == keywords[i]) {
			return true;
		}
	}
	return false;
}

bool is_identifier(string s) {
	if (isalpha(s[0])) {
		for (size_t i = 1; i < s.length(); i++) {
			if (!isalpha(s[i]) && !isdigit(s[i])) {
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

typedef enum {
	UNDEFINED = 0, SPACE = 1, TAB, NEWLINE, DO, FOR, LEFT_PARANTHESIS, RIGHT_PARANTHESIS, COMMA, SEMICOLON, LEFT_BRACKET, RIGHT_BRACKET, MINUS,
	PLUS, INCREMENT, DECREMENT, EQUAL, DOUBLE_EQUAL, GREATER_THAN_EQUAL, LESS_THAN_EQUAL, PLUS_EQUAL, MINUS_EQUAL, MULTIPLY_EQUAL, DIVIDE_EQUAL, LESS_THAN,
	GREATER_THAN, DIVIDE, MULTIPLY, OUTPUT_STREAM, INPUT_STREAM

} tokenType;
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
						cout << "IDENTIFIER" << "\t" << helping_string << endl;
					}
					else if (is_identifier(helping_string)) {
						cout << "IDENTIFIER" << "\t" << helping_string << endl;
					}
					else if (is_digit(helping_string)) {
						cout << "IDENTIFIER" << "\t" << helping_string << endl;
					}
					else {
						cout << "UNDEFINED" << "\t" << helping_string << endl;
					}
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
		t.tt = SPACE;
		t.entryOne = "SPACE";
		print = true;
		return t;
	}
	else if (c == '\t') {
		t.tt = TAB;
		t.entryOne = "TAB";
		print = true;
		return t;
	}
	else if (c == '\n') {
		t.tt = NEWLINE;
		t.entryOne = "NEWLINE";
		print = true;
		return t;
	}
	else if (c == '(') {
		t.tt = LEFT_PARANTHESIS;
		t.entryOne = "LEFT PARENTHESIS";
		print = true;
		return t;
	}
	else if (c == ')') {
		t.tt = RIGHT_PARANTHESIS;
		t.entryOne = "RIGHT PARENTHESIS";
		print = true;
		return t;
	}
	else if (c == '{') {
		t.tt = LEFT_BRACKET;
		t.entryOne = "LEFT BRACKET";
		print = true;
		return t;
	}
	else if (c == '}') {
		t.tt = RIGHT_BRACKET;
		t.entryOne = "RIGHT BRACKET";
		print = true;
		return t;
	}
	else if (c == ',') {
		t.tt = COMMA;
		t.entryOne = "COMMA";
		print = true;
		return t;
	}
	else if (c == '+') {
		char temp;
		file.get(temp);
		if (temp == '+') {
			t.tt = INCREMENT;
			t.entryOne = "INCREMENT";
			print = true;
			print = true;
			return t;
		}
		else if (temp == '=') {
			t.tt = PLUS_EQUAL;
			t.entryOne = "PLUS EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = PLUS;
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
			t.tt = DECREMENT;
			t.entryOne = "DECREMENT";
			print = true;
			return t;
		}
		else if (temp == '=') {
			t.tt = MINUS_EQUAL;
			t.entryOne = "MINUS EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = MINUS;
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
			t.tt = LESS_THAN_EQUAL;
			t.entryOne = "LESS THAN EQUAL";
			print = true;
			return t;
		}
		else if (temp == '<') {
			t.tt = OUTPUT_STREAM;
			t.entryOne = "OUTPUT STREAM";
			print = true;
			return t;
		}
		else {
			t.tt = LESS_THAN;
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
			t.tt = GREATER_THAN_EQUAL;
			t.entryOne = "GREATER THAN EQUAL";
			print = true;
			return t;
		}
		else if (temp == '>') {
			t.tt = INPUT_STREAM;
			t.entryOne = "INPUT STREAM";
			print = true;
			return t;
		}
		else {
			t.tt = GREATER_THAN;
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
			t.tt = DIVIDE_EQUAL;
			t.entryOne = "DIVIDE EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = DIVIDE;
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
			t.tt = MULTIPLY_EQUAL;
			t.entryOne = "MULTIPLY EQUAL";
			print = true;
			return t;
		}
		else {
			t.tt = MULTIPLY;
			t.entryOne = "MULTIPLY";
			print = true;
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '=') {
		char temp;
		file.get(temp);
		if (c == '=') {
			t.tt = DOUBLE_EQUAL;
			print = true;
			t.entryOne = "DOUBLE EQUAL";
			return t;
		}
		else {
			t.tt = EQUAL;
			print = true;
			t.entryOne = "EQUAL";
			t.moveBack = true;
			return t;
		}
	}
	else if (c == ';') {
		t.tt = SEMICOLON;
		print = true;
		t.entryOne = "SEMICOLON";
		return t;
	}
	else {
		helping_string += c;
		print = false;
		t.tt = UNDEFINED;
		t.entryOne = "UNDEFINED";
		return t;
	}
}
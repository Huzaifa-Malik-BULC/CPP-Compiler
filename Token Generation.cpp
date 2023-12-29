#include<iostream>
#include<fstream>
using namespace std;

fstream file;

typedef enum {
	UNDEFINED = 0, SPACE = 1, TAB, NEWLINE, DO, FOR, LEFT_PARANTHESIS, RIGHT_PARANTHESIS, COMMA, SEMICOLON, LEFT_BRACKET, RIGHT_BRACKET, MINUS,
	PLUS, INCREMENT, DECREMENT, EQUAL, DOUBLE_EQUAL, GREATER_THAN_EQUAL, LESS_THAN_EQUAL, PLUS_EQUAL, MINUS_EQUAL, MULTIPLY_EQUAL, DIVIDE_EQUAL, LESS_THAN,
	GREATER_THAN, DIVIDE, MULTIPLY, OUTPUT_STREAM, INPUT_STREAM

} tokenType;

class Token {
public:
	tokenType tt;
	string entryOne;
	int num;
	string variable;
	static Token Lexical_Analyzer(char);
	bool moveBack = false;
};

void tokenize() {
	Token t;
	char ch;

	file.open("code.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			if (t.moveBack) {
				file.unget();
				t.moveBack = false;
			}
			file.get(ch);
			t = Token::Lexical_Analyzer(ch);

			cout << t.tt << "\t" << t.entryOne << endl;
		}
	}
}

// Here I have changed something

Token Token::Lexical_Analyzer(char c) {
	Token t;

	if (c == ' ') {
		t.tt = SPACE;
		t.entryOne = "SPACE";
		return t;
	}
	else if (c == '\t') {
		t.tt = TAB;
		t.entryOne = "TAB";
		return t;
	}
	else if (c == '\n') {
		t.tt = NEWLINE;
		t.entryOne = "NEWLINE";
		return t;
	}
	else if (c == '(') {
		t.tt = LEFT_PARANTHESIS;
		t.entryOne = "LEFT PARENTHESIS";
		return t;
	}
	else if (c == ')') {
		t.tt = RIGHT_PARANTHESIS;
		t.entryOne = "RIGHT PARENTHESIS";
		return t;
	}
	else if (c == '{') {
		t.tt = LEFT_BRACKET;
		t.entryOne = "LEFT BRACKET";
		return t;
	}
	else if (c == '}') {
		t.tt = RIGHT_BRACKET;
		t.entryOne = "RIGHT BRACKET";
		return t;
	}
	else if (c == ',') {
		t.tt = COMMA;
		t.entryOne = "COMMA";
		return t;
	}
	else if (c == '+') {
		char temp;
		file.get(temp);
		if (temp == '+') {
			t.tt = INCREMENT;
			t.entryOne = "INCREMENT";
			return t;
		}
		else if (temp == '=') {
			t.tt = PLUS_EQUAL;
			t.entryOne = "PLUS EQUAL";
			return t;
		}
		else {
			t.tt = PLUS;
			t.entryOne = "PLUS";
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
			return t;
		}
		else if (temp == '=') {
			t.tt = MINUS_EQUAL;
			t.entryOne = "MINUS EQUAL";
			return t;
		}
		else {
			t.tt = MINUS;
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
			return t;
		}
		else if (temp == '<') {
			t.tt = OUTPUT_STREAM;
			t.entryOne = "OUTPUT STREAM";
			return t;
		}
		else {
			t.tt = LESS_THAN;
			t.entryOne = "LESS THAN";
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
			return t;
		}
		else if (temp == '>') {
			t.tt = INPUT_STREAM;
			t.entryOne = "INPUT STREAM";
			return t;
		}
		else {
			t.tt = GREATER_THAN;
			t.entryOne = "GREATER THAN";
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
			return t;
		}
		else {
			t.tt = DIVIDE;
			t.entryOne = "DIVIDE";
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
			return t;
		}
		else {
			t.tt = MULTIPLY;
			t.entryOne = "MULTIPLY";
			t.moveBack = true;
			return t;
		}
	}
	else if (c == '=') {
		char temp;
		file.get(temp);
		if (c == '=') {
			t.tt = DOUBLE_EQUAL;
			t.entryOne = "DOUBLE EQUAL";
			return t;
		}
		else {
			t.tt = EQUAL;
			t.entryOne = "EQUAL";
			t.moveBack = true;
			return t;
		}
	}
	else if (c == ';') {
		t.tt = SEMICOLON;
		t.entryOne = "SEMICOLON";
		return t;
	}
	else {
		t.tt = UNDEFINED;
		t.entryOne = "UNDEFINED";
		return t;
	}
}

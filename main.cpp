#include<iostream>
#include<fstream>
#include<regex>
#include<string>
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
	system("cls");
	Token t;
	char ch;

	file.open("Tokenize.txt");
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



void regularexpression()
{
	system("cls");

	ifstream file("regular_expression.txt");

	string code = "";

	regex regex_assignment("^\\s*(int|double|float|string)\\s*\\w+\\s*=\\s*(\"[^\"]*\"|\\d+(\\.\\d+)?|[A-Za-z_]\\w*)\\s*;\\s*$");
	regex regex_conditional_jump("^\\s*if\\s*\\(\\s*\\w+\\s*(\\=\\=|\\>\\=|\\<\\=)\\s*\\w\\s*\\)\\s*\\{?\\s*goto\\s+\\w+\\s*;\\s*\\}?\\s*$");
	regex regex_procedure("^\\s*\\w+\\s*\\(((\\s*\\w*\\s*)|((\\s*\\w+\\s*)(\\s*\\,\\s*\\w+\\s*)+))\\)\\s*;\\s*$");
	regex regex_copy("^\\s*[A-Za-z_]+\\w*\\s*\\=\\s*[A-Za-z_]+\\w*\\s*;\\s*$");
	regex regex_unconditonal_jump("^\\s*goto\\s+[A-Za-z_]\\w*\\s*;\\s*$");

	regex regex_for("^for\\s*\\(\\s*[a-zA-Z_]\\w*\\s*=\\s*\\w+\\s*;\\s*[a-zA-Z_]\\w*\\s*(<|<=|>|>=|==|!=)\\s*\\w+\\s*;\\s*[a-zA-Z_]\\w*\\s*[-+]\\s*[-+]?\\d*\\s*\\)\\s*\\{\\s*[A-Za-z_]+\\w*\\s*\\=\\s*[A-Za-z_]+\\w*\\s*;\\s*\\}\\s*;?$");
	regex regex_while("^\\s*while\\s*\\(\\s*[A-Za-z_]\\w*\\s*(==|<|>|>=|<=)\\s*((\\d+)|([A-Za-z_]\\w*))\\s*\\)\\s*\\{\\s*\\}\\s*$");
	regex regex_do_while("^\\s*do\\s*\\s*\\{\\s*\\}\\s*while\\s*\\(\\s*[A-Za-z_]\\w*\\s*(==|<|>|>=|<=)\\s*((\\d+)|([A-Za-z_]\\w*))\\s*\\)\\s*;\\s*$");

	regex regex_function("^(int|double|string|float|bool|void)\\s+\\w+\\((((int|double|string|float|bool|void)\\s+\\w*)|((int|double|string|float|bool|void)\\s+\\w*(\\,\\s*(int|double|string|float|bool|void)\\s+\\w*)*))\\);$");
	regex regex_switch("^\\s*switch\\s*\\(\\s*[A-Za-z_]\\w*\\s*\\)\\s*\\{\\s*(case\\s*((\\'[A-Za-z]\\')|([0-9]+))\\s*\\:\\s*(.)*\\s*(break;\\s*)?(\\s*default\\s*\\:\\s*(.)*(break;)?)?)*\\}$");
	regex regex_array("^\\s*(int|string|double|float|char)\\s+[A-Za-z_]\\w*\\s*(\\[\\s*\\d+\\s*\\])+\\s*;\\s*$");
	regex regex_pointer("^(int|float|double|char)\\s*\\*\\s*[A-Za-z_]\\w*\\s*;$");


	if (file.is_open()) {
		string line;
		while (!file.eof()) {
			getline(file, line);
			code += line;
		}

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
		else cout << "Invalid Expression" << endl;
	}



}


int main() {
	char choice;
	cout << "\t\t\t\t\tCOMPILER CONSTRUCTION" << endl;
	cout << "\n\t\t\t1.Tokenize" << endl;
	cout << "\n\t\t\t2.Regex" << endl;
	cout << "\n\t\t\tEnter your choice: ";
	cin >> choice;
	if (choice == '1') {
		tokenize();
	}
	else if (choice == '2') {
		regularexpression();
	}
	else {
		cout << "Invalid choice" << endl;
	}
}
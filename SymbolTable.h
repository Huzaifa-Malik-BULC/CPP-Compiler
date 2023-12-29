#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <vector>
using namespace std;

typedef enum {
	SPACE = 1, TAB, NEWLINE, SEMICOLON, EQUALTO, KEYWORD, UID, DIGIT, GEN_SYMBOL, SINGLE_LINE_COMMENT, MULTI_LINE_COMMENT, WHILE, PARENTHISIS, BRACKETS,
	PLUS, EQUAL, MINUS, MULT, SLASH, PLUSPLUS, MINUSMINUS, EQUALEQUAL, PLUSEQUAL, MINUSEQUAL, LESSQUAL, GREATEREQUAL, LESSGREATER, stringdata
} tokentype;

fstream lexicalfile;
struct Node {
	string uid;
	Node* next;
};

struct token {
	tokentype tt;
	string entryno;
	int num;
	string variable;
};

bool isKeyword(const string& word) {
	vector<string> keywords = { "int", "float", "string", "if", "else", "while", "for", "return", "do", "double" };

	for (const string& keyword : keywords) {
		if (word == keyword) {
			return true;
		}
	}
	return false;
}


class Symbol_Table_UID {
private:
	Node* head;
	Node* tail;
public:
	Symbol_Table_UID() {
		head = NULL;
		tail = NULL;
	}
	void enqueue(string uid) {
		Node* temp = new Node();
		temp->uid = uid;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = tail->next;
		}
	}
	void display() {
		if (head == NULL) {
			cout << "Symbol table is empty.\n";
			return;
		}
		cout << "\nSymbol table for UID :\n";
		Node* temp = head;
		while (temp != NULL) {
			cout << temp->uid << endl;
			temp = temp->next;
		}
	}
};

class Symbol_Table_DIG {
private:
	Node* head;
	Node* tail;
public:
	Symbol_Table_DIG() {
		head = NULL;
		tail = NULL;
	}
	void enqueue(string uid) {
		Node* temp = new Node();
		temp->uid = uid;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = tail->next;
		}
	}
	void display() {
		if (head == NULL) {
			cout << "Symbol table is empty.\n";
			return;
		}
		cout << "\nSymbol table for DIG :\n";
		Node* temp = head;
		while (temp != NULL) {
			cout << temp->uid << endl;
			temp = temp->next;
		}
	}
};

class Symbol_Table_string {
private:
	Node* head;
	Node* tail;
public:
	Symbol_Table_string() {
		head = NULL;
		tail = NULL;
	}
	void enqueue(string uid) {
		Node* temp = new Node();
		temp->uid = uid;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = tail->next;
		}
	}
	void display() {
		if (head == NULL) {
			cout << "Symbol table is empty.\n";
			return;
		}
		cout << "\nSymbol table for String Values :\n";
		Node* temp = head;
		while (temp != NULL) {
			cout << "\"" << temp->uid << endl;
			temp = temp->next;
		}
	}
};

Symbol_Table_UID str_uid;
Symbol_Table_DIG str_dig;
Symbol_Table_string str_val;

token mylex(fstream& file) {
	char c;
	string line;
	char next = ' ';
	token t;
	t.variable = "";
	string key;

	while (file.get(c)) {
		if (file.peek() != EOF) {
			next = file.peek();
		}
		else {
			next = ' ';
		}

		if (c == ' ') {
			t.tt = SPACE;
			t.entryno = "SPACE";
		}
		else if (c == '/' && next == '/') {
			t.tt = SINGLE_LINE_COMMENT;
			t.entryno = "Single Line Comments";
			while (c != '\n') {
				file.get(c);
			}
		}
		else if (c == '/' && next == '*') {
			t.tt = MULTI_LINE_COMMENT;
			t.entryno = "Multiline Comments";
			while (true) {
				file.get(c);
				if (c == '*' && file.peek() == '/') {
					file.get(c);
					break;
				}
			}
		}
		else if (c == '\n') {
			t.tt = NEWLINE;
			t.entryno = "Newline";
		}
		else if (isalpha(c) || c == '_') {
			t.tt = UID;
			t.entryno = "Identifier";
			t.variable += c;
			while (isalnum(file.peek()) || file.peek() == '_') {
				t.variable += file.get();
			}

			if (isKeyword(t.variable)) {
				t.tt = KEYWORD;
				t.entryno = "Keyword";
				break;
			}
			str_uid.enqueue(t.variable);
			break;
		}
		else if (c == '"') {
			t.tt = stringdata;
			string value;
			t.entryno = "stringdata";
			while (true) {
				file.get(c);

				value += c;
				if (c == '"') {
					file.get(c);
					str_val.enqueue(value);
					break;
				}
			}
		}
		else if (isdigit(c))
		{
			t.variable += c;
			while (isdigit(file.peek())) {
				c = file.get();
				t.variable += c;
			}
			str_dig.enqueue(t.variable);
			t.tt = DIGIT;
			t.entryno = "Digit";
		}
		else if (c == 'W')
		{
			t.variable += c;
			if (file.get() == 'h')
			{
				while ((c = file.get()) != 'e')
				{
					t.variable += c;
				}
			}
		}
		else if (c == '(' || c == ')' || c == '{' || c == '}')
		{
			t.tt = PARENTHISIS;
			t.variable = c;
			t.entryno = "PARENTHISIS";
		}
		else if (c == ']' || c == '[')
		{
			t.tt = BRACKETS;
			t.variable = c;
			t.entryno = "BRACKETS";
		}
		else if (c == ';')
		{
			t.tt = SEMICOLON;
			t.entryno = "SEMICOLON";
			return t;
		}
		else if (c == '+')
		{
			if (next == '+')
			{
				t.tt = PLUSPLUS;
				t.entryno = "PLUSPLUS";
				t.variable = "++";
			}
			else if (next == '=')
			{
				t.tt = PLUSEQUAL;
				t.entryno = "PLUSEQUAL";
				t.variable = "+=";
			}
			else
			{
				t.tt = PLUS;
				t.entryno = "PLUS";
			}
		}
		else if (c == '-')
		{
			if (next == '-')
			{
				t.tt = MINUSMINUS;
				t.entryno = "MINUSMINUS";
				t.variable = "--";
			}
			else if (next == '=')
			{
				t.tt = MINUSEQUAL;
				t.entryno = "MINUSEQUAL";
				t.variable = "-=";
			}
			else
			{
				t.tt = MINUS;
				t.entryno = "MINUS";
			}
		}
		else if (c == '=')
		{
			if (next == '=')
			{
				t.tt = EQUALEQUAL;
				t.entryno = "EQUALEQUAL";
				t.variable = "==";
			}
			else
			{
				t.tt = EQUAL;
				t.entryno = "EQUAL";
			}
		}
		else if (c == '<')
		{
			if (next == '=')
			{
				t.tt = LESSQUAL;
				t.entryno = "LESSQUAL";
				t.variable = "<=";
			}
			else if (next == '>')
			{
				t.tt = LESSGREATER;
				t.entryno = "LESSGREATER";
				t.variable = "<>";
			}
		}
		else if (c == '>')
		{
			if (next == '=')
			{
				t.tt = GREATEREQUAL;
				t.entryno = "GREATEREQUAL";
				t.variable = ">=";
			}
		}

		if (t.tt != SPACE) {
			break;
		}
	}
	return t;
}

int SymbolTable(string input_file) {
	token t1;
	lexicalfile.open("input.txt");

	if (!lexicalfile.is_open()) {
		cout << "Failed to open file." << endl;
		return 1;
	}

	while (true) {
		t1 = mylex(lexicalfile);

		if (lexicalfile.eof()) {
			break;
		}

		/*cout << t1.tt << " " << t1.entryno << " " << t1.variable << endl;*/
	}

	str_uid.display();
	str_dig.display();
	str_val.display();

}

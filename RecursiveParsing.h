#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include<string>
using namespace std;

struct RecursiveDescentParser {
    string input;
    size_t index;

    RecursiveDescentParser(string& input) : input(input), index(0) {}

    bool parseExp();
    bool parseTerm();
    bool parseOp();
    bool parse();
};

bool RecursiveDescentParser::parseExp() {
    if (parseTerm()) {
        while (parseOp() && parseTerm()) {

        }
        return true;
    }
    return false;
}

bool RecursiveDescentParser::parseTerm() {
    if (isdigit(input[index])) {
        while (isdigit(input[++index])) {

        }
        return true;
    }
    else if (input[index] == '(') {
        ++index;
        if (parseExp() && input[index] == ')') {
            ++index;
            return true;
        }
    }
    return false;
}

bool RecursiveDescentParser::parseOp() {
    if (input[index] == '+' || input[index] == '-' || input[index] == '*' || input[index] == '/' || input[index] == '%' || input[index] == '^') {
        ++index;
        return true;
    }
    return false;
}

bool RecursiveDescentParser::parse() {
    return parseExp() && index == input.size();
}

int RecursiveParse(string input_file) {
    ifstream inputFile(input_file);
    if (!inputFile.is_open()) {
        cerr << "Error cannot open file\n";
        return 1;
    }


    while (!inputFile.eof()) {
        string inputExpression;
        getline(inputFile, inputExpression);


        if (!inputExpression.empty()) {
            RecursiveDescentParser parser(inputExpression);

            if (parser.parse()) {
                cout << "Grammar is valid: " << inputExpression << "\n";
            }
            else {
                cout << "Grammar is invalid: " << inputExpression << "\n";
            }
        }
    }

    inputFile.close();

}
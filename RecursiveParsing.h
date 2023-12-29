#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include<string>
using namespace std;

struct RecursiveDescentParser {
    string input;
    size_t index;
    int openParenCount;
    int closeParenCount;

    RecursiveDescentParser(string& input) : input(input), index(0), openParenCount(0), closeParenCount(0) {}

    bool parseExp();
    bool parseTerm();
    bool parseOp();
    bool parse();
    bool bracketsBalanced();
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
        ++openParenCount;
        ++index;
        if (parseExp() && input[index] == ')') {
            ++closeParenCount;
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
    return parseExp() && index == input.size() && bracketsBalanced();
}

inline bool RecursiveDescentParser::bracketsBalanced() {
    return (openParenCount == closeParenCount);
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
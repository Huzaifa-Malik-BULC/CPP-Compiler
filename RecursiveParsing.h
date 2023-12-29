#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

class RecursiveDescentParser {
    std::string input;
    size_t index;
    bool num_found;

    bool parseExp();
    bool parseTerm();
    bool parseOp();

public:
    RecursiveDescentParser(const std::string&);
    bool parse();
};

int RecursiveParse(string input_file) {
    ifstream file(input_file);
    if (!file.is_open()) {
        cerr << "Error while opening file." << endl;
        return 1;
    }

    string input;
    std::getline(file, input);

    RecursiveDescentParser parser(input);

    if (parser.parse()) {
        cout << "Input is accepted." << endl;
    }
    else {
        cout << "Input is not accepted." << endl;
    }

    file.close();
    return 0;
}

RecursiveDescentParser::RecursiveDescentParser(const std::string& expr) : input(expr), index(0), num_found(false) {}

bool RecursiveDescentParser::parseExp() {
    if (parseTerm()) {
        if (input[index] != '\0') {
            while (input.size() != index) {
                if (parseOp()) {
                    parseExp();
                }
                else return false;
            }
        }
        else return true;
    }
    else return false;
}

bool RecursiveDescentParser::parseTerm() {
    if (std::isdigit(input[index])) {
        ++index;
        num_found = true;
        return parseTerm();
    }
    else if (input[index] == '(') {
        ++index;
        if (parseExp() && input[index] == ')') {
            ++index;
            return true;
        }
    }

    if (!num_found) return false;
    else {
        num_found = false;
        return true;
    }
}

bool RecursiveDescentParser::parseOp() {
    if (input[index] == '+' || input[index] == '-' || input[index] == '*') {
        ++index;
        return true;
    }
    return false;
}

bool RecursiveDescentParser::parse() {
    return parseExp() && index == input.size();
}

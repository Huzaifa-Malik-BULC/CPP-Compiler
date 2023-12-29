#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

enum class TokenType {
    NUMBER, ID, ADDOPR, MULOPR, LPAREN, RPAREN, ASSIGN, SEMICOLON, END
};

struct Token {
    TokenType type;
    string value;
};

class Parser {
    istringstream input;
    Token token;
    string output;

    void nextToken() {
        char ch;
        if (!(input >> ch)) {
            token.type = TokenType::END;
            return;
        }

        switch (ch) {
        case '+':
            token.type = TokenType::ADDOPR;
            token.value = "plus";
            break;
        case '-':
            token.type = TokenType::ADDOPR;
            token.value = "minus";
            break;
        case '*':
            token.type = TokenType::MULOPR;
            token.value = "Mul";
            break;
        case '/':
            token.type = TokenType::MULOPR;
            token.value = "Div";
            break;
        case '(':
            token.type = TokenType::LPAREN;
            break;
        case ')':
            token.type = TokenType::RPAREN;
            break;
        case '=':
            token.type = TokenType::ASSIGN;
            break;
        case ';':
            token.type = TokenType::SEMICOLON;
            break;
        default:
            if (isdigit(ch)) {
                input.putback(ch);
                int number;
                input >> number;
                token.type = TokenType::NUMBER;
                token.value = to_string(number);
            }
            else if (isalpha(ch)) {
                token.type = TokenType::ID;
                token.value = ch;
            }
            break;
        }
    }

    void match(TokenType expected) {
        if (token.type != expected) {
            throw runtime_error("Unexpected token");
        }
        if (token.type == TokenType::NUMBER || token.type == TokenType::ADDOPR || token.type == TokenType::MULOPR) {
            output += token.value + " ";
        }
        nextToken();
    }

    void factor() {
        if (token.type == TokenType::NUMBER) {
            match(TokenType::NUMBER);
        }
        else if (token.type == TokenType::LPAREN) {
            match(TokenType::LPAREN);
            output += "( ";
            expression();
            match(TokenType::RPAREN);
            output += ") ";
        }
        else {
            throw runtime_error("Factor expected");
        }
    }

    void term() {
        factor();
        while (token.type == TokenType::MULOPR) {
            match(TokenType::MULOPR);
            factor();
        }
    }

    void expression() {
        term();
        while (token.type == TokenType::ADDOPR) {
            match(TokenType::ADDOPR);
            term();
        }
    }

    void statement() {
        match(TokenType::ID);
        match(TokenType::ASSIGN);
        expression();
        match(TokenType::SEMICOLON);
    }

public:
    void parse(const string& str) {
        input = istringstream(str);
        nextToken();
        statement();
        if (token.type != TokenType::END) {
            throw runtime_error("End of input expected");
        }
    }

    void parseFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Failed to open file");
        }

        ostringstream buffer;
        buffer << file.rdbuf();
        parse(buffer.str());
    }

    string getOutput() {
        return output;
    }
};

int syntaxAnalysisAndTreeExpression(string& input_file) {
    Parser parser;
    try {

        parser.parseFromFile(input_file);
        cout << "Parsing successful. Output: " << parser.getOutput() << endl;
    }
    catch (const runtime_error& e) {
        cout << "Parsing failed: " << e.what() << endl;
    }
    return 0;
}

#pragma once
#include <iostream> //hello 
#include <stack>
#include <fstream>
using namespace std;

void solveTheEquation(string&);
int precedence(char);
int applyOp(int, int, char);
int evaluate(string);

void StatementEvaluation(string input_file) {
    fstream file(input_file);
    if (file.is_open()) {
        char ch;
        string line = "";
        while (!file.eof()) {
            file.get(ch);
            line += ch;
        }
        solveTheEquation(line);
    }
    else {
        cout << "Error while opening the file";
    }
  
}

void solveTheEquation(string& expression) {
    size_t len = 0;
    bool has_var = false;
    if (expression[expression.length() - 1] != ';') {
        cerr << "Invalid end of statement";
        exit(1);
    }
    else {
        while (expression[expression.length() - 1] == ';') {
            expression.pop_back();
        }
    }

    for (len; len < expression.length(); len++) {
        if (!has_var) {
            if (expression[len] != ' ') {
                if (expression[len] >= 'a' && expression[len] <= 'z' || expression[len] >= 'A' && expression[len] <= 'Z') {
                    has_var = true;
                }
                else {
                    cout << "Invalid or Missing Variable Name";
                    exit(1);
                }
            }
            else continue;
        }
        if (expression[len] == '=') {
            len++;
            expression = expression.substr(len, expression.length());
            cout << "Answer => " << evaluate(expression);
            exit(0);
        }
    }
    cerr << "Invalid expression. Missing Assignment operator";
    exit(1);
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
}
int evaluate(string tokens) {
    int i;
    stack <int> values;
    stack <char> ops;

    for (i = 0; i < tokens.length(); i++) {
        if (tokens[i] == ' ')
            continue;

        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

        else if (isdigit(tokens[i])) {
            int val = 0;

            while (i < tokens.length() &&
                isdigit(tokens[i]))
            {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }

            values.push(val);
            i--;
        }

        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            if (!ops.empty())
                ops.pop();
        }

        else
        {
            while (!ops.empty() && precedence(ops.top())
                >= precedence(tokens[i])) {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}


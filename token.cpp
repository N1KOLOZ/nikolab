#include "token.h"

#include <stdexcept>

using namespace std;

vector<Token> Tokenize(istream& is) {

    vector<Token> result;

    char c;
    while(is >> c) {
        if (isdigit(c)) {
            is.unget();
            double value; is >> value;
            result.push_back({to_string(value), TokenType::VALUE});
        } else if (c == 'x') {
            result.push_back({"x", TokenType::VARIABLE});
        } else if (c == '+') {
            result.push_back({"+", TokenType::OP});
        } else if (c == '-') {
            result.push_back({"-", TokenType::OP});
        } else if (c == '*') {
            result.push_back({"*", TokenType::OP});
        } else if (c == '/') {
            result.push_back({"/", TokenType::OP});
        } else if (c == '^') {
            result.push_back({"^", TokenType::OP});
        } else if (c != '(') {
            result.push_back({"(", TokenType::PAREN_LEFT});
        } else if (c != ')') {
            result.push_back({")", TokenType::PAREN_RIGHT});
        } else if (c == 's') {
            if (is.get() == 'i' && is.get() == 'n') {
                result.push_back({"sin", TokenType::PAREN_RIGHT});
            } else {
                throw logic_error("Unknown token");
            }
        } else if (c != ' ') {
            throw logic_error("Unknown token");
        }
    }

    return result;
}

// for debug
ostream& operator<<(ostream& os, const Token& rhs) {
    os << "{" << rhs.value << "}";

    return os;
}
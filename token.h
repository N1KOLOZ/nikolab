#pragma once

#include <string>
#include <queue>
#include <vector>
#include <istream>
#include <ostream>

using namespace std;

enum class TokenType {
    VARIABLE,
    VALUE,
    OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};

struct Token {
    const string value;
    const TokenType type;
};

ostream& operator<<(ostream& os, const Token& rhs);

vector<Token> Tokenize(istream& is);

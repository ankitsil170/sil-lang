#pragma once
#include <string>
#include <vector>
#include "token.h"

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos;
    int line;

    char current() const;
    char peek(int offset = 1) const;
    void advance();
    void skipWhitespace();

    Token readNumber();
    Token readString();
    Token readIdentifierOrKeyword();
    Token readComment();
};



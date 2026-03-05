#pragma once
#include <string>

enum class TokenType {
    // Literals
    NUMBER,
    STRING,
    IDENTIFIER,

    // Keywords
    PRINT,
    IF,

    // Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    ASSIGN,

    // Comparison
    GREATER,
    LESS,
    GREATER_EQ,
    LESS_EQ,
    EQUAL_EQUAL,
    NOT_EQUAL,

    // Delimiters
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    // Special
    NEWLINE,
    END_OF_FILE,
    COMMENT,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType type, std::string value, int line)
        : type(type), value(std::move(value)), line(line) {}
};

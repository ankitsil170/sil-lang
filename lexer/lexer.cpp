#include "lexer.h"
#include <stdexcept>
#include <cctype>

Lexer::Lexer(const std::string& source)
    : source(source), pos(0), line(1) {}

char Lexer::current() const {
    if (pos >= source.size()) return '\0';
    return source[pos];
}

char Lexer::peek(int offset) const {
    if (pos + offset >= source.size()) return '\0';
    return source[pos + offset];
}

void Lexer::advance() {
    if (pos < source.size()) pos++;
}

void Lexer::skipWhitespace() {
    while (pos < source.size() && (current() == ' ' || current() == '\t' || current() == '\r')) {
        advance();
    }
}

Token Lexer::readNumber() {
    std::string num;
    bool hasDecimal = false;
    while (pos < source.size() && (std::isdigit(current()) || (current() == '.' && !hasDecimal))) {
        if (current() == '.') hasDecimal = true;
        num += current();
        advance();
    }
    return Token(TokenType::NUMBER, num, line);
}

Token Lexer::readString() {
    advance(); // skip opening quote
    std::string str;
    while (pos < source.size() && current() != '"') {
        if (current() == '\\') {
            advance();
            if (current() == 'n') str += '\n';
            else if (current() == 't') str += '\t';
            else str += current();
        } else {
            str += current();
        }
        advance();
    }
    advance(); // skip closing quote
    return Token(TokenType::STRING, str, line);
}

Token Lexer::readIdentifierOrKeyword() {
    std::string word;
    while (pos < source.size() && (std::isalnum(current()) || current() == '_')) {
        word += current();
        advance();
    }
    if (word == "print") return Token(TokenType::PRINT, word, line);
    if (word == "if")    return Token(TokenType::IF, word, line);
    return Token(TokenType::IDENTIFIER, word, line);
}

Token Lexer::readComment() {
    std::string comment;
    while (pos < source.size() && current() != '\n') {
        comment += current();
        advance();
    }
    return Token(TokenType::COMMENT, comment, line);
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (pos < source.size()) {
        skipWhitespace();

        if (pos >= source.size()) break;

        char c = current();

        if (c == '\n') {
            tokens.push_back(Token(TokenType::NEWLINE, "\\n", line));
            line++;
            advance();
            continue;
        }

        if (c == '#') {
            readComment(); // skip comments silently
            continue;
        }

        if (std::isdigit(c)) {
            tokens.push_back(readNumber());
            continue;
        }

        if (c == '"') {
            tokens.push_back(readString());
            continue;
        }

        if (std::isalpha(c) || c == '_') {
            tokens.push_back(readIdentifierOrKeyword());
            continue;
        }

        switch (c) {
        case '+': tokens.push_back(Token(TokenType::PLUS, "+", line)); advance(); break;
        case '-': tokens.push_back(Token(TokenType::MINUS, "-", line)); advance(); break;
        case '*': tokens.push_back(Token(TokenType::STAR, "*", line)); advance(); break;
        case '/': tokens.push_back(Token(TokenType::SLASH, "/", line)); advance(); break;
        case '(': tokens.push_back(Token(TokenType::LPAREN, "(", line)); advance(); break;
        case ')': tokens.push_back(Token(TokenType::RPAREN, ")", line)); advance(); break;
        case '{': tokens.push_back(Token(TokenType::LBRACE, "{", line)); advance(); break;
        case '}': tokens.push_back(Token(TokenType::RBRACE, "}", line)); advance(); break;
        case '=':
            if (peek() == '=') {
                tokens.push_back(Token(TokenType::EQUAL_EQUAL, "==", line));
                advance(); advance();
            } else {
                tokens.push_back(Token(TokenType::ASSIGN, "=", line));
                advance();
            }
            break;
        case '>':
            if (peek() == '=') {
                tokens.push_back(Token(TokenType::GREATER_EQ, ">=", line));
                advance(); advance();
            } else {
                tokens.push_back(Token(TokenType::GREATER, ">", line));
                advance();
            }
            break;
        case '<':
            if (peek() == '=') {
                tokens.push_back(Token(TokenType::LESS_EQ, "<=", line));
                advance(); advance();
            } else {
                tokens.push_back(Token(TokenType::LESS, "<", line));
                advance();
            }
            break;
        case '!':
            if (peek() == '=') {
                tokens.push_back(Token(TokenType::NOT_EQUAL, "!=", line));
                advance(); advance();
            } else {
                tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, c), line));
                advance();
            }
            break;
        default:
            tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, c), line));
            advance();
            break;
        }
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "", line));
    return tokens;
}

#include "token.h"

// Token implementation is header-only for this simple version.
// Future: add token type to string conversion for debugging.

std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case TokenType::NUMBER:      return "NUMBER";
    case TokenType::STRING:      return "STRING";
    case TokenType::IDENTIFIER:  return "IDENTIFIER";
    case TokenType::PRINT:       return "PRINT";
    case TokenType::IF:          return "IF";
    case TokenType::PLUS:        return "PLUS";
    case TokenType::MINUS:       return "MINUS";
    case TokenType::STAR:        return "STAR";
    case TokenType::SLASH:       return "SLASH";
    case TokenType::ASSIGN:      return "ASSIGN";
    case TokenType::GREATER:     return "GREATER";
    case TokenType::LESS:        return "LESS";
    case TokenType::GREATER_EQ:  return "GREATER_EQ";
    case TokenType::LESS_EQ:     return "LESS_EQ";
    case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
    case TokenType::NOT_EQUAL:   return "NOT_EQUAL";
    case TokenType::LPAREN:      return "LPAREN";
    case TokenType::RPAREN:      return "RPAREN";
    case TokenType::LBRACE:      return "LBRACE";
    case TokenType::RBRACE:      return "RBRACE";
    case TokenType::NEWLINE:     return "NEWLINE";
    case TokenType::END_OF_FILE: return "EOF";
    default:                     return "UNKNOWN";
    }
}

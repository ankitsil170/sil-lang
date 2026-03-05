#include "parser.h"
#include <stdexcept>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), pos(0) {}

Token& Parser::current() {
    return tokens[pos];
}

Token& Parser::peek(int offset) {
    size_t idx = pos + offset;
    if (idx >= tokens.size()) return tokens.back();
    return tokens[idx];
}

Token Parser::consume() {
    Token t = tokens[pos];
    if (pos < tokens.size() - 1) pos++;
    return t;
}

bool Parser::check(TokenType type) {
    return current().type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) { consume(); return true; }
    return false;
}

void Parser::skipNewlines() {
    while (check(TokenType::NEWLINE)) consume();
}

std::unique_ptr<ProgramNode> Parser::parse() {
    auto program = std::make_unique<ProgramNode>();
    skipNewlines();
    while (!check(TokenType::END_OF_FILE)) {
        auto stmt = parseStatement();
        if (stmt) program->statements.push_back(std::move(stmt));
        skipNewlines();
    }
    return program;
}

NodePtr Parser::parseStatement() {
    if (check(TokenType::PRINT)) {
        return parsePrint();
    }
    if (check(TokenType::IF)) {
        return parseIf();
    }
    if (check(TokenType::IDENTIFIER)) {
        std::string name = current().value;
        consume();
        if (check(TokenType::ASSIGN)) {
            consume(); // eat '='
            return parseAssignment(name);
        }
        throw std::runtime_error("Unexpected identifier: " + name);
    }
    if (check(TokenType::NEWLINE)) {
        consume();
        return nullptr;
    }
    throw std::runtime_error("Unexpected token: " + current().value + " on line " + std::to_string(current().line));
}

NodePtr Parser::parsePrint() {
    consume(); // eat 'print'
    if (!check(TokenType::LPAREN))
        throw std::runtime_error("Expected '(' after print");
    consume(); // eat '('
    auto expr = parseExpression();
    if (!check(TokenType::RPAREN))
        throw std::runtime_error("Expected ')' after print expression");
    consume(); // eat ')'
    return std::make_unique<PrintNode>(std::move(expr));
}

NodePtr Parser::parseAssignment(const std::string& name) {
    auto expr = parseExpression();
    return std::make_unique<AssignNode>(name, std::move(expr));
}

NodePtr Parser::parseIf() {
    consume(); // eat 'if'
    auto condition = parseExpression();
    if (!check(TokenType::LBRACE))
        throw std::runtime_error("Expected '{' after if condition");
    consume(); // eat '{'
    skipNewlines();
    std::vector<NodePtr> body;
    while (!check(TokenType::RBRACE) && !check(TokenType::END_OF_FILE)) {
        auto stmt = parseStatement();
        if (stmt) body.push_back(std::move(stmt));
        skipNewlines();
    }
    if (!check(TokenType::RBRACE))
        throw std::runtime_error("Expected '}' to close if block");
    consume(); // eat '}'
    return std::make_unique<IfNode>(std::move(condition), std::move(body));
}

NodePtr Parser::parseExpression() {
    return parseComparison();
}

NodePtr Parser::parseComparison() {
    auto left = parseAddSub();
    while (check(TokenType::GREATER) || check(TokenType::LESS) ||
           check(TokenType::GREATER_EQ) || check(TokenType::LESS_EQ) ||
           check(TokenType::EQUAL_EQUAL) || check(TokenType::NOT_EQUAL)) {
        std::string op = current().value;
        consume();
        auto right = parseAddSub();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

NodePtr Parser::parseAddSub() {
    auto left = parseMulDiv();
    while (check(TokenType::PLUS) || check(TokenType::MINUS)) {
        std::string op = current().value;
        consume();
        auto right = parseMulDiv();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

NodePtr Parser::parseMulDiv() {
    auto left = parsePrimary();
    while (check(TokenType::STAR) || check(TokenType::SLASH)) {
        std::string op = current().value;
        consume();
        auto right = parsePrimary();
        left = std::make_unique<BinaryOpNode>(op, std::move(left), std::move(right));
    }
    return left;
}

NodePtr Parser::parsePrimary() {
    if (check(TokenType::NUMBER)) {
        double val = std::stod(current().value);
        consume();
        return std::make_unique<NumberNode>(val);
    }
    if (check(TokenType::STRING)) {
        std::string val = current().value;
        consume();
        return std::make_unique<StringNode>(val);
    }
    if (check(TokenType::IDENTIFIER)) {
        std::string name = current().value;
        consume();
        return std::make_unique<IdentifierNode>(name);
    }
    if (check(TokenType::LPAREN)) {
        consume(); // eat '('
        auto expr = parseExpression();
        if (!check(TokenType::RPAREN))
            throw std::runtime_error("Expected ')'");
        consume(); // eat ')'
        return expr;
    }
    throw std::runtime_error("Unexpected token in expression: '" + current().value + "' on line " + std::to_string(current().line));
}

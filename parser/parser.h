#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../lexer/token.h"

// ─── AST Node Types ───────────────────────────────────────────────────────────

struct ASTNode {
    virtual ~ASTNode() = default;
};

using NodePtr = std::unique_ptr<ASTNode>;

// Expressions
struct NumberNode : ASTNode {
    double value;
    explicit NumberNode(double v) : value(v) {}
};

struct StringNode : ASTNode {
    std::string value;
    explicit StringNode(std::string v) : value(std::move(v)) {}
};

struct IdentifierNode : ASTNode {
    std::string name;
    explicit IdentifierNode(std::string n) : name(std::move(n)) {}
};

struct BinaryOpNode : ASTNode {
    std::string op;
    NodePtr left;
    NodePtr right;
    BinaryOpNode(std::string op, NodePtr l, NodePtr r)
        : op(std::move(op)), left(std::move(l)), right(std::move(r)) {}
};

// Statements
struct PrintNode : ASTNode {
    NodePtr expr;
    explicit PrintNode(NodePtr e) : expr(std::move(e)) {}
};

struct AssignNode : ASTNode {
    std::string name;
    NodePtr expr;
    AssignNode(std::string n, NodePtr e) : name(std::move(n)), expr(std::move(e)) {}
};

struct IfNode : ASTNode {
    NodePtr condition;
    std::vector<NodePtr> body;
    IfNode(NodePtr cond, std::vector<NodePtr> b)
        : condition(std::move(cond)), body(std::move(b)) {}
};

struct ProgramNode : ASTNode {
    std::vector<NodePtr> statements;
};

// ─── Parser ───────────────────────────────────────────────────────────────────

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    std::unique_ptr<ProgramNode> parse();

private:
    std::vector<Token> tokens;
    size_t pos;

    Token& current();
    Token& peek(int offset = 1);
    Token consume();
    bool check(TokenType type);
    bool match(TokenType type);
    void skipNewlines();

    NodePtr parseStatement();
    NodePtr parsePrint();
    NodePtr parseAssignment(const std::string& name);
    NodePtr parseIf();
    NodePtr parseExpression();
    NodePtr parseComparison();
    NodePtr parseAddSub();
    NodePtr parseMulDiv();
    NodePtr parsePrimary();
};

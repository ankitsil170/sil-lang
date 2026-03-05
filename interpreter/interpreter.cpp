#include "interpreter.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

void Interpreter::execute(ProgramNode* program) {
    for (auto& stmt : program->statements) {
        executeStatement(stmt.get());
    }
}

void Interpreter::executeStatement(ASTNode* node) {
    if (auto* p = dynamic_cast<PrintNode*>(node)) {
        execPrint(p);
    } else if (auto* a = dynamic_cast<AssignNode*>(node)) {
        execAssign(a);
    } else if (auto* i = dynamic_cast<IfNode*>(node)) {
        execIf(i);
    } else {
        throw std::runtime_error("Unknown statement type");
    }
}

Value Interpreter::evaluate(ASTNode* node) {
    if (auto* n = dynamic_cast<NumberNode*>(node)) {
        return n->value;
    }
    if (auto* s = dynamic_cast<StringNode*>(node)) {
        return s->value;
    }
    if (auto* id = dynamic_cast<IdentifierNode*>(node)) {
        return env.get(id->name);
    }
    if (auto* bin = dynamic_cast<BinaryOpNode*>(node)) {
        return evalBinaryOp(bin);
    }
    throw std::runtime_error("Unknown expression type");
}

Value Interpreter::evalBinaryOp(BinaryOpNode* node) {
    Value left  = evaluate(node->left.get());
    Value right = evaluate(node->right.get());

    // String concatenation with +
    if (node->op == "+" && std::holds_alternative<std::string>(left)) {
        return std::get<std::string>(left) + valueToString(right);
    }

    // Numeric operations
    auto toNum = [&](const Value& v, const std::string& side) -> double {
        if (std::holds_alternative<double>(v)) return std::get<double>(v);
        throw std::runtime_error("Cannot use '" + node->op + "' on string (" + side + " side)");
    };

    double l = toNum(left, "left");
    double r = toNum(right, "right");

    if (node->op == "+")  return l + r;
    if (node->op == "-")  return l - r;
    if (node->op == "*")  return l * r;
    if (node->op == "/") {
        if (r == 0) throw std::runtime_error("Division by zero");
        return l / r;
    }
    if (node->op == ">")  return static_cast<double>(l > r);
    if (node->op == "<")  return static_cast<double>(l < r);
    if (node->op == ">=") return static_cast<double>(l >= r);
    if (node->op == "<=") return static_cast<double>(l <= r);
    if (node->op == "==") return static_cast<double>(l == r);
    if (node->op == "!=") return static_cast<double>(l != r);

    throw std::runtime_error("Unknown operator: " + node->op);
}

void Interpreter::execPrint(PrintNode* node) {
    Value val = evaluate(node->expr.get());
    std::cout << valueToString(val) << "\n";
}

void Interpreter::execAssign(AssignNode* node) {
    Value val = evaluate(node->expr.get());
    env.set(node->name, val);
}

void Interpreter::execIf(IfNode* node) {
    Value cond = evaluate(node->condition.get());
    if (isTruthy(cond)) {
        for (auto& stmt : node->body) {
            executeStatement(stmt.get());
        }
    }
}

std::string Interpreter::valueToString(const Value& val) {
    if (std::holds_alternative<double>(val)) {
        double d = std::get<double>(val);
        // Print integers cleanly
        if (d == std::floor(d) && !std::isinf(d)) {
            return std::to_string(static_cast<long long>(d));
        }
        std::string s = std::to_string(d);
        // Trim trailing zeros
        s.erase(s.find_last_not_of('0') + 1);
        if (s.back() == '.') s.pop_back();
        return s;
    }
    return std::get<std::string>(val);
}

bool Interpreter::isTruthy(const Value& val) {
    if (std::holds_alternative<double>(val)) {
        return std::get<double>(val) != 0.0;
    }
    return !std::get<std::string>(val).empty();
}

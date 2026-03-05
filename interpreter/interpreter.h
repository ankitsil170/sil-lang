#pragma once
#include "../parser/parser.h"
#include "../runtime/environment.h"

class Interpreter {
public:
    void execute(ProgramNode* program);

private:
    Environment env;

    void executeStatement(ASTNode* node);
    Value evaluate(ASTNode* node);

    Value evalBinaryOp(BinaryOpNode* node);
    void execPrint(PrintNode* node);
    void execAssign(AssignNode* node);
    void execIf(IfNode* node);

    std::string valueToString(const Value& val);
    bool isTruthy(const Value& val);
};

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"

static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    std::ostringstream buf;
    buf << file.rdbuf();
    return buf.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "sil-lang v1.0\n";
        std::cerr << "Usage: sil <file.sil>\n";
        std::cerr << "Example: sil examples/hello.sil\n";
        return 1;
    }

    std::string filename = argv[1];

    // Warn if extension is not .sil
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".sil") {
        std::cerr << "[warning] File does not have .sil extension: " << filename << "\n";
    }

    try {
        std::string source = readFile(filename);

        // 1. Lex
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();

        // 2. Parse
        Parser parser(std::move(tokens));
        auto program = parser.parse();

        // 3. Interpret
        Interpreter interpreter;
        interpreter.execute(program.get());

    } catch (const std::exception& e) {
        std::cerr << "[sil error] " << e.what() << "\n";
        return 1;
    }

    return 0;
}

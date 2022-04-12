#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "lexer.hpp"
#include "expressionAnalysis.hpp"
#include "compiler.hpp"


#include "debug.hpp"
#include "token.hpp"

void compileFile(char* path) {
    std::cout << "Reading file: " << path << std::endl;

    std::ifstream file;
    file.open(path, std::ios::in);
    std::stringstream data;
    std::string line;

    while (std::getline(file, line)) {
        data << line;
    }

    file.close();

    std::string sInput = data.str();

    std::cout << "Lexing" << std::endl;

    std::vector<Token> tokenizedInput = scan(sInput);

    std::cout << "Expression Analysis" << std::endl;

    std::vector<Expression> expressions = analyse(tokenizedInput);

    std::cout << "Code Generation" << std::endl;

    std::string code = compile(expressions);
    std::cout << code;
}

int main(int argc, char* argv[]) {
    compileFile(argv[1]);
}

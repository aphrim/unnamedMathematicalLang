#include <sstream>
#include <iostream>

#include "compiler.hpp"

static std::string genVarAss (Expression expr);
static std::string genArithmatic (Expression expr);
static std::string genLoop (Expression expr);

struct Compiler {
    int curScope;
    std::vector<std::vector<std::string>> declaredVariables;
} compiler;

std::string compileExpr(Expression expr) {
    std::cout << "Compiling expr" << std::endl;
    switch (expr.type) {
        case EXPRESSION_VAR_ASS:
            return genVarAss(expr);
        case EXPRESSION_ARITHMATIC:
            return genArithmatic(expr);
        case EXPRESSION_LOOP:
            return genLoop(expr);
        case EXPRESSION_END:
            return "}";
    }
    return "";
}

std::string compile (std::vector<Expression> code) {
    std::stringstream ret;
    ret <<"\
int main() {";

    compiler = Compiler();

    compiler.curScope = 0;
    compiler.declaredVariables.push_back(std::vector<std::string>());

    for (int i = 0; i < code.size() - 1; i++) {
        Expression expr = code[i];
        ret << compileExpr(expr);
    }
    
    ret << "}";

    return ret.str();
}

static bool isVariableDeclared(std::string varName) {
    for (std::vector<std::string> stack : compiler.declaredVariables) {
        for (std::string var : stack) {
            if (var == varName) return true;
        }
    }
    return false;
}

static void declareVariable(std::string varName) {
    compiler.declaredVariables[compiler.declaredVariables.size() - 1].push_back(varName);
}

static std::string genVarAss(Expression expr) {
    std::cout << "Compiling Vari Assign" << std::endl;
    if (isVariableDeclared(expr.target.str())) {
        return expr.target.str() + " = " + expr.arguments[0].str() + ';';
    } else {
        declareVariable(expr.target.str());
        return "float " + expr.target.str() + " = " + expr.arguments[0].str() + ';';
    }

}
static std::string genArithmatic(Expression expr) {
    std::string op = expr.op.op();
    std::stringstream ret;

    if (not isVariableDeclared(expr.target.str())) {
        declareVariable(expr.target.str());
        ret << "float ";
    }
    ret << expr.target.str() << " = ";

    for (int i = 0; i < expr.arguments.size() - 1; i++)
        ret << expr.arguments[i].str() << " " << op << " ";
    ret << expr.arguments[expr.arguments.size() - 1].str() << ";";

    return ret.str();
}

static std::string genLoop(Expression expr) {
    std::stringstream ret;
    compiler.declaredVariables.push_back(std::vector<std::string>());

    std::string t = expr.target.str();
    std::string s = expr.arguments[0].str();
    std::string e = expr.arguments[1].str();
    
    ret << "for (";

    if (not isVariableDeclared(t)) {
        ret << "float ";
        declareVariable(t);
    }

    ret << t << " = " << s << ";";
    ret << t << " > " << e << " ? ";
    ret << t << " <= " << e << " : ";
    ret << t << " >= " << e << ";";
    ret << t << " > " << e << " ? ";
    ret << t << "--" << " : " << t << "++;) {";

    return ret.str();
}

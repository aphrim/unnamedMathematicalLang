#define DEBUG_EXPRESSIONS
#include <iostream>

#include "expressionAnalysis.hpp"
#include "debug.hpp"

static Expression analyseExpr        (std::vector<Token>& code, int& index);
static Expression analyseFunctionCall(std::vector<Token>& code, int& index);
static Expression analyseArithmatic  (std::vector<Token>& code, int& index);
static Expression analyseAssignment  (std::vector<Token>& code, int& index);
static Expression analyseFunctionDef (std::vector<Token>& code, int& index);
static Expression analyseLoop        (std::vector<Token>& code, int& index);


Expression analyseExpr(std::vector<Token>& code, int& index) {
    Token firstToken = code[index];
    Token secondToken = code[++index];
    switch (firstToken.type) {
        case TOKEN_LEFT_PAREN: {
            if (secondToken.type == TOKEN_VARIABLE) {} /* Todo: Analyse Function Call */
            else return analyseArithmatic(code, index);
        }
        case TOKEN_VARIABLE: {
            return analyseAssignment(code, index);
        }
        case TOKEN_LOOP: {
            return analyseLoop(code, index);
        }
        case TOKEN_END: {
#ifdef DEBUG_EXPRESSIONS
    std::cout << "Expression End" << std::endl;
#endif
            return Expression({type: EXPRESSION_END});
        }
        case TOKEN_EOF: {
            Expression ret;
            ret.type = EXPRESSION_EOF;
            return ret;
        }
    }
    std::cout << "BIG BAD!!!!!!!!!!!!!" << std::endl;
    Expression ret; //Temp to avoid bad alloc
    ret.type = EXPRESSION_VAR_ASS;
    return ret;
}

std::vector<Expression> analyse(std::vector<Token> code) {
    std::vector<Expression> ret;
    int index = 0;
   
    for (;;) {
        if (index >= code.size() - 1) break;
        Expression expr = analyseExpr(code, index);
        ret.push_back(expr);
        if (expr.type == EXPRESSION_EOF) break;
    }

    return ret;
    
}

static Expression analyseArithmatic(std::vector<Token>& code, int& index) {
    Expression ret;
    Token op = code[index];
    std::vector<Token> operands;
    Token target;


    for (;;) {
        Token t = code[++index];
        if (t.type == TOKEN_ARROW) break;
        if (t.type == TOKEN_LEFT_PAREN) break; //Todo: Error
        operands.push_back(t);
    }
    target = code[++index];

    index += 2;

    ret.type = EXPRESSION_ARITHMATIC;
    ret.op = op;
    ret.arguments = operands;
    ret.target = target;


#ifdef DEBUG_EXPRESSIONS
    std::cout << "Arithmatic Expression" << std::endl;
    printToken(op);
    for (Token t: ret.arguments) {
        printToken(t);
    }
    printToken(ret.target);
#endif

    return ret;
}


static Expression analyseAssignment(std::vector<Token>& code, int& index) {
    Expression ret;
    ret.target = code[--index];
    ret.arguments = std::vector<Token>({ code[index += 2] });
    ret.type = EXPRESSION_VAR_ASS;

#ifdef DEBUG_EXPRESSIONS
    std::cout << "Variable Assignment Expression" << std::endl;
    printToken(ret.target);
    printToken(ret.arguments[0]);
#endif

    index += 2;

    return ret;
}


static Expression analyseLoop(std::vector<Token>& code, int& index) {
    Expression ret;
    ret.target = code[index];
    ret.arguments.push_back(code[index += 2]);
    ret.arguments.push_back(code[index += 2]);
    ret.type = EXPRESSION_LOOP;

#ifdef DEBUG_EXPRESSIONS
    std::cout << "Loop Expression" << std::endl;
    printToken(ret.target);
    printToken(ret.arguments[0]);
    printToken(ret.arguments[1]);
#endif
     index++;

    return ret;
}








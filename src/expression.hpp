#ifndef expressionh
#define expressionh

#include <vector>

#include "token.hpp"

typedef enum {
    EXPRESSION_VAR_ASS, EXPRESSION_ARITHMATIC,
    EXPRESSION_FUNC_CALL, EXPRESSION_FUNC_DEFINE,
    EXPRESSION_BLOCK_END, EXPRESSION_BLOCK_START,
    EXPRESSION_LOOP, EXPRESSION_END,
    EXPRESSION_EOF,
} ExpressionType;

typedef struct {
    ExpressionType type; 
    std::vector<Token> arguments;
    Token target;
    Token op;
} Expression;


#endif

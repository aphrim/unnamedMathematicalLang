#ifndef expressionanalh
#define expressionanalh

#include <vector>

#include "token.hpp"
#include "expression.hpp"

std::vector<Expression> analyse (std::vector<Token> code);

#endif

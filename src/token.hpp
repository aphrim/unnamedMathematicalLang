#include <cstdint>
#include <vector>
#ifndef tokenh
#define tokenh

enum TokenType {
	TOKEN_NUMBER, TOKEN_STRING, TOKEN_TRUE, TOKEN_FALSE, TOKEN_VARIABLE,

	TOKEN_LOOP, TOKEN_WHILE, TOKEN_FUNC, TOKEN_IF, TOKEN_INCLUDE,
    TOKEN_FROM, TOKEN_TO, TOKEN_END,

	TOKEN_RIGHT_PAREN, TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_BRACKET, TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACE, TOKEN_LEFT_BRACE,

    TOKEN_EQUAL_EQUAL,
    TOKEN_LESS, TOKEN_GREATER,
    TOKEN_GREATER_EQUAL, TOKEN_LESS_EQUAL,
    TOKEN_BANG_EQUAL,

	TOKEN_ARROW,
    TOKEN_ADD, TOKEN_SUB, TOKEN_MULT, TOKEN_DIV, TOKEN_MOD,

	TOKEN_COLON, TOKEN_SEMICOLON,	

	TOKEN_ERROR,
	TOKEN_EOF,
};

struct Token {
	TokenType type;
	int line;
	std::vector<uint8_t> data;

    std::string str() {
        if (type == TOKEN_NUMBER)
            return std::to_string(num());
        else 
            return std::string(data.begin(), data.end());
    }

    double num() {
        return *(double*)(&data[0]);
    }

    std::string op() {
        switch (type) {
            case TOKEN_ADD:
                return "+";
            case TOKEN_SUB:
                return "-";
            case TOKEN_MULT:
                return "*";
            case TOKEN_DIV:
                return "/";
            case TOKEN_MOD:
                return "%";
        }
        return "";
    }

};
#endif

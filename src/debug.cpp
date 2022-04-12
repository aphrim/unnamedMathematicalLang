#include <iostream>
#include <vector>
#include "debug.hpp"


void printToken(Token token) {
    TokenType type = token.type;
    std::vector<uint8_t> data = token.data;
	switch (type) {
		case TOKEN_ERROR: {
			std::cout << "TOKEN_ERROR" << std::endl;
			break;
		}
		case TOKEN_NUMBER: {
			std::cout << "TOKEN_NUMER: " << token.num() << std::endl;
			break;
		}
		case TOKEN_STRING: {
			std::cout << "TOKEN_STRING: " << token.str() << std::endl;
			break;
		}
		case TOKEN_VARIABLE:
			std::cout << "TOKEN_VARIABLE: ";
			for (uint8_t c : data) {
				std::cout << (char) c;
			}
			std::cout << std::endl;
			break;
        case TOKEN_ARROW:
            std::cout << "TOKEN_ARROW" << std::endl;
            break;
		case TOKEN_LOOP:
			std::cout << "TOKEN_LOOP" << std::endl;
			break;
		case TOKEN_FROM:
			std::cout << "TOKEN_FROM" << std::endl;
			break;
		case TOKEN_TO:
			std::cout << "TOKEN_TO" << std::endl;
			break;
		case TOKEN_WHILE:
			std::cout << "TOKEN_WHILE" << std::endl;
			break;
		case TOKEN_FUNC:
			std::cout << "TOKEN_FUNC" << std::endl;
			break;
		case TOKEN_IF:
			std::cout << "TOKEN_IF" << std::endl;
			break;
		case TOKEN_INCLUDE:
			std::cout << "TOKEN_INCLUDE" << std::endl;
			break;
		case TOKEN_RIGHT_PAREN:
			std::cout << "TOKEN_RIGHT_PAREN" << std::endl;
			break;
		case TOKEN_LEFT_PAREN:
			std::cout << "TOKEN_LEFT_PAREN" << std::endl;
			break;
		case TOKEN_RIGHT_BRACKET:
			std::cout << "TOKEN_RIGHT_BRACKET" << std::endl;
			break;
		case TOKEN_LEFT_BRACKET:
			std::cout << "TOKEN_LEFT_BRACKET" << std::endl;
			break;
		case TOKEN_RIGHT_BRACE:
			std::cout << "TOKEN_RIGHT_BRACE" << std::endl;
			break;
		case TOKEN_LEFT_BRACE:
			std::cout << "TOKEN_LEFT_BRACE" << std::endl;
			break;
		case TOKEN_FALSE:
			std::cout << "TOKEN_FALSE" << std::endl;
			break;
		case TOKEN_TRUE:
			std::cout << "TOKEN_TRUE" << std::endl;
			break;
		case TOKEN_EOF:
			std::cout << "TOKEN_EOF" << std::endl;
			break;
		case TOKEN_SEMICOLON:
			std::cout << "TOKEN_SEMICOLON" <<std::endl;
			break;
		case TOKEN_COLON:
			std::cout << "TOKEN_COLON" << std::endl;
			break;
        case TOKEN_ADD:
            std::cout << "TOKEN_ADD" << std::endl;
            break;
        case TOKEN_SUB:
            std::cout << "TOKEN_SUB" << std::endl;
            break;
        case TOKEN_MULT:
            std::cout << "TOKEN_MULT" << std::endl;
            break;
        case TOKEN_DIV:
            std::cout << "TOKEN_DIV" << std::endl;
            break;
        case TOKEN_MOD:
            std::cout << "TOKEN_MOD" << std::endl;
            break;
		default:
			std::cout << "Unknown Token" << std::endl;
	}

}

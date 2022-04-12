#include <iostream>
#include "lexer.hpp"
#include "debug.hpp"

static void tokenizeError(std::string error, int line) {
	std::cout << "Error on line " << line << " : " << error << std::endl;
}

static bool isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c == '_');
}

static bool isNumber(char c) {
	return (c >= '0' && c <= '9');
}

static char getNext(int& charIndex, std::string& code) {
	if (charIndex + 1 <= code.size()) {
		return code[charIndex++];
	} else {
		return '\0';
	}
}

static char peek(int& charIndex, std::string& code, int offset) {
	return code[charIndex + offset];
}

static bool matchString(int& charIndex, std::string& code, std::string toMatch) {
	for (int t = 0; t < toMatch.size(); t++) {
		if (code[charIndex + t - 1] != toMatch[t]) {
			return false;
		}
	}
	if (isAlpha(code[charIndex + toMatch.size() - 1]) || isNumber(code[charIndex + toMatch.size() - 1])) return false;
	charIndex += toMatch.size() - 1;
	return true;
}

static Token makeToken(int& charIndex, int& line, std::string& code, TokenType type, std::vector<uint8_t> data = {}) {
	Token token;
	token.type = type;
	token.line = line;
	token.data = data;
	return token;
}

static void skipWhitespace(int& charIndex, int& line, std::string& code) {
	char c = peek(charIndex, code, 0);
	if (!(c == ' ' || c == '\t' || c == '\n')) return;
	while(true) {
		c = getNext(charIndex, code);
		if (!(c == ' ' || c == '\t' || c == '\n')) {
			charIndex--;
			break;
		}
		if (c == '\n') line++;
	}
	return;
}

static void skipLine(int& charIndex, int& line, std::string& code) {
    char c = peek(charIndex, code, 0);
    if (c == '\n') return;
    while (true) {
        if (c == '\n' || c == '\0') { line++; break; }
        c = getNext(charIndex, code);
    }
    return;
}

static std::string getVariable(int& charIndex, std::string& code) {
	std::string ret;
	charIndex--;
	while(true) {
		char c = code[charIndex];
		if (c == '\0') break;
		if (isAlpha(c) || isNumber(c)) ret.push_back(c);
		else break;
		charIndex++;
	}
	return ret;
}

static double getNumber(int& charIndex, std::string& code) {
	std::string consumedNum;
    bool decimal = false;
	charIndex--;
	while(true) {
		char c = code[charIndex];
		if (c == '\0') break;
		if (isNumber(c)) consumedNum.push_back(c);
        else if (c == '.') {
            if (decimal) /*Error*/ std::cout << "More than 1 decimal place in number";
            else {
                decimal = true;
                consumedNum.push_back(c);
            }
        } else break;
		charIndex++;
	}
	return std::stod(consumedNum);

}

static std::string getString(int& charIndex, std::string& code, int& line) {
	std::string ret;
	while(true) {
		char c = code[charIndex];
		if(c == '\0') { tokenizeError("Unterminated String", line); break; }
		if(c == '"' && code[charIndex - 1] != '\\') break;
		if(c == '\\' && code[charIndex - 1] != '\\') { charIndex++; continue; }
		if(c == '\n' || (c == 'n' && code[charIndex - 1] == '\\')) line++;
		ret.push_back(c);

		charIndex++;
	}
	charIndex++;
	return ret;

}

static Token getToken(int& charIndex, int& line, std::string& code) {
	skipWhitespace(charIndex, line, code);
	char first = getNext(charIndex, code);
	switch (first) {
		case '(':
                return makeToken(charIndex, line, code, TOKEN_LEFT_PAREN);
        case ')':
                return makeToken(charIndex, line, code, TOKEN_RIGHT_PAREN);
        case '{':
                return makeToken(charIndex, line, code, TOKEN_LEFT_BRACKET);
        case '}':
                return makeToken(charIndex, line, code, TOKEN_RIGHT_BRACKET);
		case ';':
			return makeToken(charIndex, line, code, TOKEN_SEMICOLON);
		case ':':
			return makeToken(charIndex, line, code, TOKEN_COLON);
		case '-':
			if (matchString(charIndex, code, "->")) return makeToken(charIndex, line, code, TOKEN_ARROW);
			return makeToken(charIndex, line, code, TOKEN_SUB);
		case '"': {
			std::string str = getString(charIndex, code, line);
			std::vector<uint8_t> tokenData;
			for (char c : str) tokenData.push_back((uint8_t) c);
			return makeToken(charIndex, line, code, TOKEN_STRING, tokenData);
			}
        case '=': {
            if (matchString(charIndex, code, "==")) return makeToken(charIndex, line, code, TOKEN_EQUAL_EQUAL);
            break;
        }
        case '<': {
            if (matchString(charIndex, code, "<=")) return makeToken(charIndex, line, code, TOKEN_LESS_EQUAL);
            return makeToken(charIndex, line, code, TOKEN_LESS);
        }
        case '>': {
            if (matchString(charIndex, code, ">=")) return makeToken(charIndex, line, code, TOKEN_GREATER_EQUAL);
            return makeToken(charIndex, line, code, TOKEN_GREATER);
        }
        case '+': 
            return makeToken(charIndex, line, code, TOKEN_ADD);
        case '*': 
            return makeToken(charIndex, line, code, TOKEN_MULT);
        case '/': 
            return makeToken(charIndex, line, code, TOKEN_DIV);
        case '%': 
            return makeToken(charIndex, line, code, TOKEN_MOD);
        case '!': {
            if (matchString(charIndex, code, "!=")) return makeToken(charIndex, line, code, TOKEN_BANG_EQUAL);
            break;
        }
        case '#': {
            skipLine(charIndex, line, code);
            return getToken(charIndex, line, code);
        }
		case '\0': {
			return makeToken(charIndex, line, code, TOKEN_EOF);
        }
		case 'f':
			if (matchString(charIndex, code, "false")) return makeToken(charIndex, line, code, TOKEN_FALSE);	
			if (matchString(charIndex, code, "func")) return makeToken(charIndex, line, code, TOKEN_FUNC);
			if (matchString(charIndex, code, "from")) return makeToken(charIndex, line, code, TOKEN_FROM);
			break;
        case 'l':
			if (matchString(charIndex, code, "loop")) return makeToken(charIndex, line, code, TOKEN_LOOP);
        case 'e':
            if (matchString(charIndex, code, "end")) return makeToken(charIndex, line, code, TOKEN_END);
		case 'i':
			if (matchString(charIndex, code, "if")) return makeToken(charIndex, line, code, TOKEN_IF);
			if (matchString(charIndex, code, "include")) return makeToken(charIndex, line, code, TOKEN_INCLUDE);
			break;
		case 't':
			if (matchString(charIndex, code, "true")) return makeToken(charIndex, line, code, TOKEN_TRUE);
			if (matchString(charIndex, code, "to")) return makeToken(charIndex, line, code, TOKEN_TO);
			break;
	}
	if (isAlpha(first)) {
		std::string variableName = getVariable(charIndex, code);
		std::vector<uint8_t> tokenData;
		for (char c : variableName) tokenData.push_back((uint8_t) c);
		Token token = makeToken(charIndex, line, code, TOKEN_VARIABLE, tokenData);
		return token;
	} else if (isNumber(first)) {
		int number = getNumber(charIndex, code);
		uint8_t tokenArr[9];
		double* loc = (double*)(&tokenArr[0]);
		*loc = number;
		std::vector<uint8_t> tokenData;
		for (uint8_t n : tokenArr) tokenData.push_back(n);
		Token token = makeToken(charIndex, line, code, TOKEN_NUMBER, tokenData);
		return token;
	} else {
		tokenizeError("Unexpected Character", line);
		return makeToken(charIndex, line, code, TOKEN_ERROR);
	}
}

std::vector<Token> scan(std::string& code) {
    std::vector<Token> ret;
	int cur = 0;
	int line = 0;
	while (true) {
		Token token = getToken(cur, line, code);
        ret.push_back(token);
        if (token.type == TOKEN_EOF) break;
	}
	return ret;

}

#pragma once
#include <string>

enum TokenType {
	TOKEN_NONE, //uninitialized token word
	TOKEN_UKNOWN_IDENTIFIER,
	TOKEN_TYPE,
	TOKEN_FUNC_IDENTIFIER,
	TOKEN_VAR_IDENTIFIER
};

struct TokenWord {
	TokenWord() : type(TOKEN_NONE) {}
	TokenWord(const std::string& _word) : word(_word), type(TOKEN_NONE) {}
	TokenWord(const std::string& _word, TokenType _type) : word(_word), type(_type) {}

	std::string word;
	TokenType type;
};
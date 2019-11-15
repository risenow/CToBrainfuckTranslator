#pragma once
#include "BFMemoryManagerIntegrator.h"
#include "CScope.h"
#include "CVarTypesRegister.h"
#include "CPPAbstractSyntaxTree.h"
#include <string>


constexpr unsigned int symbols_allowed_in_value_word_count = 10;
const char symbols_allowed_in_value_word[] = { 'f', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

enum CTranslationState {
	STATE_DECLARATION = (1u << 0),
	STATE_DEFINITION  = (1u << 1),
	STATE_VARIABLE    = (1u << 2),
	STATE_FUNCTION    = (1u << 3),
	STATE_STRUCTURE   = (1u << 4),
	STATE_INIT        = (1u << 5),
	STATE_VALUE       = (1u << 6)
};

typedef int translation_state;

struct CTranslationStateInfo {
	int regIntValue;
	float regFloatValue;
	double regDoubleValue;
	unsigned int regUintValue;

	std::string regID;
	CVarType* regType;
	enum_t regValueType;

	void set_value_reg(const std::string& v, enum_t type) {
		switch (type) {
		case CVarTypesRegister::TYPE_INT:
			regIntValue = std::stoi(v);
			break;
		case CVarTypesRegister::TYPE_FLOAT:
			regFloatValue = std::stof(v);
			break;
		case CVarTypesRegister::TYPE_DOUBLE:
			regDoubleValue = std::stod(v);
			break;
		}
		regValueType = type;
	}
};

enum LogicWordType {
	TYPE_WORD, VALUE_WORD, IDENTIFICATOR_WORD, INVALID_WORD, NEWID_WORD, OPERATOR_WORD
};

struct LogicWord {
	LogicWord(LogicWordType _type, const std::string& _word):type(_type), word(_word) {
	}

	LogicWordType type;
	std::string word;
};

class CCode {
public:
	CCode();
	CCode(const std::string& code_str);

	std::string translate();
private:
	void initialize();
	std::string read_logic_line();
	std::vector<LogicWord> decompose_line_into_logic_words(const std::string& logic_line);
	LogicWord create_logic_word_from_str(const std::string& logic_word);
	enum_t determine_type_of_word_value(const std::string& word);
	bool is_operator_word(const std::string& word);
	bool is_operator_symbol(char symb);
	bool is_value_word(const std::string& word);

	std::string c_code;
	unsigned int current_char_index;

	bool is_last_line;

	BFMemoryBlock base_block;
	BFMemoryManagerIntegrator memory_manager_integrator;
	CScope scope;
	CVarTypesRegister types_register;
	CTranslationStateInfo state_info;
	translation_state state;

	CPPAbstractSyntaxTree cppAST;
};

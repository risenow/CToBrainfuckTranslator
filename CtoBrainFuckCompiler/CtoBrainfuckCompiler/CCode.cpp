#include "stdafx.h"
#include "CCode.h"
#include "BFMemoryBlockBuilder.h"

CCode::CCode() {}
CCode::CCode(const std::string& _c_code): c_code(_c_code) {}
void CCode::initialize() {
	cppAST.BuildFrom("int test;");
	types_register.initialize(&memory_manager_integrator);
	scope.addTypes(types_register.getBaseVarTypes());
	state = 0;
	current_char_index = 0;
	is_last_line = false;
}
std::string CCode::translate(){
	initialize();

	std::string in_block_code;
	std::string result;

	BFMemoryBlockBuilder base_block_builder(memory_manager_integrator.cmdPreReserveMask());
	base_block_builder.setDepthLevel(0);

	memory_manager_integrator.initializeInsideBlockCodeGeneration();
	while (!is_last_line) {
		std::vector<LogicWord> decomposed_line = decompose_line_into_logic_words(read_logic_line());

		for (int i = 0; i < decomposed_line.size(); i++){
			if (state == 0) {
				switch (decomposed_line[i].type)
				{
				case TYPE_WORD:
					state |= STATE_DECLARATION;
					CVarType* type;
					scope.getType(decomposed_line[i].word, type);
					state_info.regType = type;
					break;
				}
			}

			if ((state & STATE_DECLARATION) == (STATE_DECLARATION)) {
				switch (decomposed_line[i].type)
				{
				case NEWID_WORD:
					state |= STATE_VARIABLE;
					state_info.regID = decomposed_line[i].word;
					break;
				}
			}

			if ((state & (STATE_DECLARATION | STATE_VARIABLE)) == (STATE_DECLARATION | STATE_VARIABLE)) {
				switch (decomposed_line[i].type)
				{
				case OPERATOR_WORD:
					if (decomposed_line[i].word == "=") 
						state |= STATE_INIT;
					break;
				}
			}

			if ((state & (STATE_DECLARATION | STATE_VARIABLE | STATE_INIT)) == (STATE_DECLARATION | STATE_VARIABLE | STATE_INIT)) {
				switch (decomposed_line[i].type)
				{
				case VALUE_WORD:
					state |= STATE_VALUE;
					state_info.set_value_reg(decomposed_line[i].word, determine_type_of_word_value(decomposed_line[i].word));
					break;
				}
			}
		}

		//******
		if ((state & STATE_DECLARATION) == STATE_DECLARATION) {

			if ((state & STATE_VARIABLE) == STATE_VARIABLE) {
				CVarPrototype var_prototype = CVarPrototype(state_info.regID, state_info.regType);
				base_block_builder.append(&memory_manager_integrator, var_prototype);
				CVar var = base_block_builder.getLastVar();
				scope.addVar(var);
				if ((state & STATE_INIT) == STATE_INIT) {
					switch (state_info.regValueType) {
						case CVarTypesRegister::TYPE_INT:
							in_block_code += state_info.regType->getOperationsSet().getConstAssign()->kernel(var, state_info.regIntValue);
							break;
					}
				}
			}
		}
	}

	base_block = base_block_builder.build(&memory_manager_integrator);
	result += memory_manager_integrator.cmdCreate(base_block.getMask());
	result += memory_manager_integrator.cmdOperateWithMaskedMemory(base_block.getMask(), in_block_code);

	return result;
}

std::string CCode::read_logic_line() {
	unsigned int reading_start_char_index = current_char_index;
	while (c_code[current_char_index] != ';' && current_char_index < c_code.size()) {
		current_char_index++;
	}
	unsigned int logic_line_end = current_char_index;
	if (current_char_index >= c_code.size() - 1) {
		is_last_line = true;
	}
	else
		current_char_index++;

	return c_code.substr(reading_start_char_index, logic_line_end - reading_start_char_index);
}

LogicWord CCode::create_logic_word_from_str(const std::string& logic_word) {
	if (is_operator_word(logic_word))
		return LogicWord(OPERATOR_WORD, logic_word);
	if (is_value_word(logic_word))
		return LogicWord(VALUE_WORD, logic_word);
	CVar var;
	if (scope.getVar(logic_word, var))
		return LogicWord(IDENTIFICATOR_WORD, logic_word);
	CFunc func;
	if (scope.getFunc(logic_word, func))
		return LogicWord(IDENTIFICATOR_WORD, logic_word);
	CVarType* type;
	if (scope.getType(logic_word, type))
		return LogicWord(TYPE_WORD, logic_word);

	return LogicWord(NEWID_WORD, logic_word);
}

std::vector<LogicWord> CCode::decompose_line_into_logic_words(const std::string& logic_line) {
	std::vector<LogicWord> logic_words;
	
	unsigned int current_char_index = 0;
	std::string temp_word;
	std::string temp_op_word;
	bool is_operator_word = false;
	for (int i = 0; i < logic_line.size(); i++) {
		if (logic_line[i] == ' ')
			continue;
		temp_word += logic_line[i];

		if (i == (logic_line.size() - 1)) {
			logic_words.push_back(create_logic_word_from_str(temp_word));
			temp_word = "";
			continue;
		}

		char next_char = logic_line[i + 1];
		bool next_char_is_operator_symbol = is_operator_symbol(next_char);
		if (!is_operator_word && (next_char == ' ' || next_char_is_operator_symbol)) {
			logic_words.push_back(create_logic_word_from_str(temp_word));
			temp_word = "";
			if (next_char_is_operator_symbol)
				is_operator_word = true;
			continue;
		}
		if (is_operator_word && (next_char == ' ' || !next_char_is_operator_symbol)) {
			logic_words.push_back(create_logic_word_from_str(temp_word));
			temp_word = "";
			is_operator_word = false;
		}
		/*if (logic_line[i] != ' ' && !is_operator_word) {
			temp_word += logic_line[i];
		}
		else {
			logic_words.push_back(create_logic_word_from_str(temp_word));
			temp_word = "";
		}*/
	}
	//logic_words.push_back(create_logic_word_from_str(temp_word));

	return logic_words;
}

enum_t CCode::determine_type_of_word_value(const std::string& word) {
	bool is_real = false;
	bool is_float = false;
	if (word.find('.') != -1)
		is_real = true;
	if (word[word.size() - 1] == 'f')
		is_float = true;
	if (is_real && is_float)
		return CVarTypesRegister::TYPE_FLOAT;
	if (is_real)
		return CVarTypesRegister::TYPE_DOUBLE;
	return CVarTypesRegister::TYPE_INT;
}
bool CCode::is_operator_word(const std::string& word) {
	for (int i = 0; i < OPERATOR_WORD_COUNT; i++) {
		if (word == OperatorWords[i])
			return true;
	}
	return false;
}
bool CCode::is_operator_symbol(char symb) {
	for (int i = 0; i < OPERATOR_SYMBS_COUNT; i++) {
		if (symb == OperatorSymbols[i])
			return true;
	}
	return false;
}
bool is_symbol_allowed_in_value_word(char c) {
	for (int i = 0; i < symbols_allowed_in_value_word_count; i++)
		if (c == symbols_allowed_in_value_word[i])
			return true;
	return false;
}
bool CCode::is_value_word(const std::string& word) {
	for (int i = 0; i < word.size(); i++) {
		if (!is_symbol_allowed_in_value_word(word[i]))
			return false;
	}
	return true;
}
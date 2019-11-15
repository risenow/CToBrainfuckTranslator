#include "stdafx.h"
/*
#include <utility>
#include <regex>
#include <algorithm>
#include "BinaryOperationKernel.h"
#include "UnaryOperationKernel.h"
#include "ConstInitializeOperationKernel.h"
#include "CtoBrainfuckTranslator.h"
#include "compile_utils.h"
#include "variable_group_index_logic_guard.h"

CtoBrainfuckCompiler::CtoBrainfuckCompiler() {
	types_register.initialize(&memory_manager);
	//memory_manager.initializeNullCell(types_register.typeCellPointer());
}
CtoBrainfuckCompiler::~CtoBrainfuckCompiler() {}

WORD_TYPE CtoBrainfuckCompiler::word_type(const std::string& word) { //tested
	std::regex number("(\\+|-)?[[:digit:]]+");
	std::regex real_number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?(f)?");
	std::regex identificator("[[:alpha:]]+([[:digit:]]+)?");
	std::regex operation("(\\+|\\-|\\*|\\/|\\=)");
	if (std::regex_match(word, number) || std::regex_match(word, real_number))
		return CONSTANT_VALUE_WORD;
	for (int i = 0; i < types_supported; i++) {
		if (word == type_specificator_strings[i])
			return TYPE_SPECIFICATOR_WORD;
	}
	if (std::regex_match(word, identificator))
		return IDENTIFICATOR_WORD;
	if (std::regex_match(word, operation))
		return OPERATION_WORD;
	return INVALID_WORD;
}
VAR_TYPE CtoBrainfuckCompiler::word_value_type(const std::string& value_word) {
	bool is_real = false;
	bool is_float = false;
	if (value_word.find('.') != -1)
		is_real = true;
	if (value_word[value_word.size() - 1] == 'f')
		is_float = true;
	if (is_real && is_float)
		return VAR_TYPE_FLOAT;
	if (is_real)
		return VAR_TYPE_DOUBLE;
	return VAR_TYPE_INT;
}
OPER_TYPE CtoBrainfuckCompiler::word_operation_type(const std::string& oper_word) {
	if (oper_word.size() > 1)
		return TYPE_OPERATION_INVALID;
	switch (oper_word[0])
	{
	case '+':
		return TYPE_OPERATION_PLUS;
		break;
	case '-':
		return TYPE_OPERATION_MINUS;
		break;
	case '/':
		return TYPE_OPERATION_DEVIDE;
		break;
	case '*':
		return TYPE_OPERATION_DEVIDE;
		break;
	default:
		return TYPE_OPERATION_INVALID;
		break;
	}
	return TYPE_OPERATION_INVALID;
}
std::string CtoBrainfuckCompiler::brainfuck_debug_out(const CVar& v) {
	std::string result;
	//result += jump_to(memory_manager.memoryPosition(), v.address());
	//result += ".";
	return result;
}
std::vector<std::string> CtoBrainfuckCompiler::decompose_line(const std::string& line) {
	const char SPACE_CHAR = ' ';
	const char ASSIGN_CHAR = '=';
	const char PLUS_CHAR = '+';
	const char MINUS_CHAR = '-';
	const char MULT_CHAR = '*';
	const char DIV_CHAR = '/';
	const char OPEN_BRACKET_CHAR = '(';
	const char CLOSE_BRACKET_CHAR = ')';
	const char CODE_LINE_END_CHAR = ';';

	std::vector<std::string> words;
	int char_index_start = 0;
	const unsigned int char_index_end_size = 9;
	std::array<std::pair<char, int>, char_index_end_size> char_index_end = {};// = 0;
	bool flag = true;
	while (flag) {
		char_index_start++;
		char_index_end[0] = std::make_pair(SPACE_CHAR,         line.find(SPACE_CHAR,         char_index_start)); //EXCLUSIVE
		char_index_end[1] = std::make_pair(ASSIGN_CHAR,        line.find(ASSIGN_CHAR,        char_index_start));
		char_index_end[2] = std::make_pair(PLUS_CHAR,          line.find(PLUS_CHAR,          char_index_start));
		char_index_end[3] = std::make_pair(MINUS_CHAR,         line.find(MINUS_CHAR,         char_index_start));
		char_index_end[4] = std::make_pair(MULT_CHAR,          line.find(MULT_CHAR,          char_index_start));
		char_index_end[5] = std::make_pair(DIV_CHAR,           line.find(DIV_CHAR,           char_index_start));
		char_index_end[6] = std::make_pair(OPEN_BRACKET_CHAR,  line.find(OPEN_BRACKET_CHAR,  char_index_start));
		char_index_end[7] = std::make_pair(CLOSE_BRACKET_CHAR, line.find(CLOSE_BRACKET_CHAR, char_index_start));
		char_index_end[8] = std::make_pair(CODE_LINE_END_CHAR, line.find(CODE_LINE_END_CHAR, char_index_start)); //EXCLUSIVE
		std::sort(char_index_end.rbegin(), char_index_end.rend(), [](const std::pair<char, int>& v1, const std::pair<char, int>& v2)->bool {return (v1.second > v2.second); });
		char_index_start--;
		for (int i = 0; i < char_index_end_size; i++) {
			if (char_index_end[i].second != -1 && (char_index_end[i].first == SPACE_CHAR || char_index_end[i].first == CODE_LINE_END_CHAR)) {
				words.push_back(line.substr(char_index_start, char_index_end[i].second - char_index_start));
				char_index_start += (char_index_end[i].second - char_index_start) + 1;
				break;
			}
			else if (char_index_end[i].second != -1) {
				words.push_back(line.substr(char_index_start, char_index_end[i].second - char_index_start));
				words.push_back(line.substr(char_index_start + 1, 1));
				char_index_start += (char_index_end[i].second - char_index_start) + 1;
				break;
			}
			else if (i == char_index_end_size - 1)
				flag = false;
	}
	}
	return words;
}
operation_translation_result CtoBrainfuckCompiler::expression_translate(const std::vector<std::string>& expression_words) {
	variable_group_index_logic_guard group_id_guard(memory_manager.localGroupIndex());
	operation_translation_result result;

	int current_word;

	if (expression_words.size() == 1) {
		WORD_TYPE type = word_type(expression_words[0]);
		CVarType* var_type;
		switch (type) {
		case IDENTIFICATOR_WORD: {
			var_type = memory_manager.var(expression_words[0]).type();

			//must not be deleted as result stack var
			CVariableMemoryLocation& stack_var = memory_manager.registerStackVar(var_type);
			stack_var.moveToUpperGroup();
			
			result.result_var_address = stack_var.address();//memory_manager.stack_var(stack_var_index);
			result.bf_code = var_type->assign_operation->kernel(stack_var, memory_manager.var(expression_words[0])).bf_code;//assign_operation(memory_manager.stack_var(result.stack_index), memory_manager.var(expression_words[0]), var_type);

			memory_manager.localGroupFree();
			return result;
		}

		case CONSTANT_VALUE_WORD: {
			var_type = types_register.typeByWord(expression_words[0]);

			//must not be deleted as result stack var
			CVariableMemoryLocation& stack_var = memory_manager.registerStackVar(var_type);
			stack_var.moveToUpperGroup();
			
			result.result_var_address = stack_var.address();
			result.bf_code = var_type->const_initialize_operation->kernel(stack_var, std::stoi(expression_words[0]));//const_init_assign_operation(memory_manager.stack_var(result.stack_index), std::stoi(expression_words[0]), var_type);

			memory_manager.localGroupFree();
			return result;
		}
		}
	}

	std::string operand1_word = expression_words[0];
	std::string operand2_word = expression_words[2];
	std::string operation_word = expression_words[1];

	WORD_TYPE operand1_word_type = word_type(expression_words[0]);
	WORD_TYPE operand2_word_type = word_type(expression_words[2]);
	OPER_TYPE operation_type = word_operation_type(expression_words[1]);


	if (operand1_word_type == IDENTIFICATOR_WORD && operand2_word_type == IDENTIFICATOR_WORD) {
		CVariableMemoryLocation operand1_var = memory_manager.var(operand1_word);
		switch (operation_type)
		{
		case TYPE_OPERATION_PLUS:
			result = operand1_var.type()->plus_operation->kernel(memory_manager.var(operand1_word), memory_manager.var(operand2_word));
			memory_manager.stackVarByAddress(result.result_var_address).moveToUpperGroup();
			break;
		default:
			break;
		}
	}
	if (expression_words.size() == 3) {
		memory_manager.localGroupFree();
		return result;
	}
	//add a stack word (prototype "__stack__pointer___" + index)(prototype index + "__stack__pointer")
	std::vector<std::string> new_expr_words;// = { ("__stack__pointer___" + std::to_string(result.stack_index)) };
	new_expr_words.insert(new_expr_words.begin() + 1, expression_words.begin() + 3, expression_words.end());

	result = expression_translate(new_expr_words);
	memory_manager.stackVarByAddress(result.result_var_address).moveToUpperGroup();

	memory_manager.localGroupFree();
	return result;
}
std::string CtoBrainfuckCompiler::translate(const std::string& c_code) {
	std::string brainfuck_code = "";
	maskloc_t base_block = memory_manager.cmdReserveMaskFor(;
	brainfuck_code += memory_manager.cmdCreate()
	int c_code_current_line_start_index = 0;
	int c_code_end_line_char_index = 0;
	//var registration and initialization
	c_code_end_line_char_index = c_code.find(';', c_code_current_line_start_index);
	while (c_code_end_line_char_index != -1) {
		//decompose lines into words
		std::vector<std::string> temp_words = decompose_line(c_code.substr(c_code_current_line_start_index, c_code_end_line_char_index - c_code_current_line_start_index + 1));
		//delete all spaces from words
		std::vector<std::string> words(temp_words.size());
		for (int i = 0; i < temp_words.size(); i++)
			for (int j = 0; j < temp_words[i].size(); j++) {
				if (temp_words[i].at(j) != ' ')
					words[i] += temp_words[i].at(j);
			}

		//determine type of variable
		CVarType* var_type = types_register.typeByWord(words[0]);


		//check if variable name is supported
		bool variable_name_authorized = true;
		for (int i = 0; i < 5; i++) {
			if (words[1].find(var_name_unauthorized_chars[i]) != -1)
				variable_name_authorized = false;
		}

		//var registration
		if (variable_name_authorized) {
			memory_manager.registerVar(words[1], var_type);

			if (words.size() > 2) {
				if (words[2] == "=") {
					operation_translation_result expression_translation = expression_translate(std::vector<std::string>(words.begin() + 3, words.end()));
					brainfuck_code += expression_translation.bf_code;
					brainfuck_code += var_type->assign_operation->kernel(memory_manager.var(words[1]), CVariableMemoryLocation(memory_manager.stackVarByAddress(expression_translation.result_var_address))).bf_code;
				}
			}
		}
		c_code_current_line_start_index = c_code_end_line_char_index + 1;
		c_code_end_line_char_index = c_code.find(';', c_code_current_line_start_index);
	}
	return brainfuck_code;
}
std::string CtoBrainfuckCompiler::translate_debug(const std::string& c_code, const std::vector<std::string>& var_names) {
	std::string result = translate(c_code);
	for (int i = 0; i < var_names.size(); i++)
		result += jump_to(memory_manager.memoryPosition(), memory_manager.var(var_names[i]).address()) + ".";
	return result;
}*/
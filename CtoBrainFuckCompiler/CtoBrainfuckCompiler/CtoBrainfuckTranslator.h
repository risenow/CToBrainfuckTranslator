/*#pragma once
#include <string>
#include <map>
#include <vector>
#include <array>
#include <initializer_list>
#include "CVar.h"
#include "BFMemoryManagerIntegrator.h"
#include "CVarTypesRegister.h"
#include "variable_type.h"
#include "oper_type.h"
#include "word_type.h"
#include "operation_translation_result.h"
*/
/*
MAIN CLASS FOR C TO BRAINFUCK COMPILATION
Use Instruction:
invoke CtoBrainfuckCompiler::translate(<c-code>)   -> returns brainfuck code as result
invoke CtoBrainfuckCompiler::translate(<c-code>, <array-of-var-names>) ->returns brainfuck code with <array-of-var-names> out in console as result
*/
/*
class CtoBrainfuckCompiler { //refactoring
	char operations_chars[3] = { '*', '+' , '='}; //deprecated
	const unsigned int mul_operation_char_in = 0; //deprecated
	const unsigned int plus_operation_char_in = 1; //deprecated
	const unsigned int assign_operation_char_in = 2; //deprecated

	const unsigned int types_supported = 4; //deprecated

	std::string type_specificator_strings[4] = { "int", "char", "float", "double" }; //deprecated
	const unsigned int int_spec_signature_in = 0; //deprecated
	const unsigned int char_spec_signature_in = 1; //deprecated
	const unsigned int float_spec_signature_in = 2; //deprecated
	const unsigned int double_spec_signature_in = 3; //deprecated

	char var_name_unauthorized_chars[5] = {'!', '#', '@', '$', '%'}; // deprecated

	BFMemoryManagerIntegrator memory_manager;
	CVarTypesRegister types_register;

	WORD_TYPE word_type(const std::string& word); //get type of word got from <decompose_line>
	VAR_TYPE word_value_type(const std::string& value_word); //type of const value from wrom word got from <decompose_line> 
	OPER_TYPE word_operation_type(const std::string& operation_word); //type of operation got from <decompose_line>

	std::string brainfuck_debug_out(const CVar& v); //may be it must be in compile utils 

	operation_translation_result expression_translate(const std::vector<std::string>& expression_words); //eval expressions translation

	std::vector<std::string> decompose_line(const std::string& line); //devide line into words
public:
	CtoBrainfuckCompiler();
	~CtoBrainfuckCompiler();

	std::string translate(const std::string& c_code); //main translation func
	std::string translate_debug(const std::string& c_code, const std::vector<std::string>& var_names); //translation func with debug output of vars with var_names
};*/


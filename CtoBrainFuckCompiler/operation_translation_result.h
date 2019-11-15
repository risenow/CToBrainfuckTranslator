#pragma once
#include <string>
#include "compile_utils_defs.h"
#include "CVariable.h"

struct operation_translation_result{
	std::string bf_code;
	address_t result_var_address;
	
	operation_translation_result() : bf_code(""){}
	operation_translation_result(const std::string& _bf_code, address_t _stack_var_address): bf_code(_bf_code), result_var_address(_stack_var_address) {}
};

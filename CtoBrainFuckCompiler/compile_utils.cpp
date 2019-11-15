#include "stdafx.h"
#include "compile_utils.h"
#include "CMemoryManager.h"

/*
std::string jump_to(unsigned int& memory_pos, unsigned int new_pos) {
	int cell_num = new_pos - memory_pos;
	unsigned int iter_num = abs(cell_num);
	memory_pos = new_pos;

	std::string result = "";
	if (cell_num > 0)
		for (int i = 0; i < iter_num; i++)
			result = result + ">";
	if (cell_num < 0)
		for (int i = 0; i < iter_num; i++)
			result = result + "<";
	return result;
}
std::string cell_to_null(CMemoryManager* memory_manager, unsigned int cell_pos) {
	std::string result;
	result += jump_to(memory_manager->memoryPosition(), cell_pos);
    result += "[-]";
	return result;
}

unsigned int get_int_var_sign_cell_address(const CVariableMemoryLocation& v) {
	return v.address();
}
unsigned int get_int_var_value_cell_address(const CVariableMemoryLocation& v) {
	return v.address() + 1;
}*/
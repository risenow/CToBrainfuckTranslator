#pragma once
#include "compile_utils_defs.h"

class variable_group_index_logic_guard {
	index_t* group_index;
public:
	variable_group_index_logic_guard(unsigned int& _group_index) {
		group_index = &_group_index;
		(*group_index)++;
	}
	~variable_group_index_logic_guard() {
		(*group_index)--;
	}
};

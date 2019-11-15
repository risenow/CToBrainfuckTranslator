#include "stdafx.h"
#include "BFDynamicMemoryJumper.h"
#include <iostream>
#include <fstream>
#include <assert.h>

BFDynamicMemoryJumper::BFDynamicMemoryJumper() {}
BFDynamicMemoryJumper::BFDynamicMemoryJumper(const std::string& bft_file_name) {
	load(bft_file_name);
}
void BFDynamicMemoryJumper::load(const std::string& bft_file_name) {
	std::ifstream file(bft_file_name);
	assert(file.is_open());
	std::getline(file, jump_template);
}

std::string BFDynamicMemoryJumper::jump(const std::string& bf_code_block) {
	std::string result = jump_template;
	size_t index = 0;
	while (true){
		index = result.find(REPLACE_SIGNATURE, index);
		if (index == std::string::npos)
			break;
		result.replace(index, REPLACE_SIGNATURE.size(), bf_code_block);
		index += bf_code_block.size();
	}
	return result;
}
#pragma once
#include <string>

const std::string REPLACE_SIGNATURE = "#";

class BFDynamicMemoryJumper {
public:
	BFDynamicMemoryJumper();
	BFDynamicMemoryJumper(const std::string& bft_file_name);

	void load(const std::string& bft_file_name);

	std::string jump(const std::string& bf_code_block);
private:
	std::string jump_template;
};
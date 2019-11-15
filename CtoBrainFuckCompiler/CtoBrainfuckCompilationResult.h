#pragma once
#include <string>

//prototype
class CtoBrainfuckCompilationResult {
	std::string program_name;
	std::string bf_code;
	std::string errors;

	const std::string extension_str = ".bf";
public:
	CtoBrainfuckCompilationResult();
	CtoBrainfuckCompilationResult(const std::string& program_name, const std::string& bf_code, const std::string& errors);

	void out();
};

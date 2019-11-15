#pragma once
#include <string>

//prototype
class CProgramConfiguration {
	std::string program_name;
	bool optimization;
public:
	CProgramConfiguration();
	CProgramConfiguration(const std::string& program_name, bool optimization);
};

#pragma once
#include <string>

class MachineConfiguration {
	size_t memory_size;
public:
	MachineConfiguration();
	MachineConfiguration(const std::string& file_name);
	~MachineConfiguration();
};

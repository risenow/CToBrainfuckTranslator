#pragma once
#include <string>
#include "CVarType.h"

struct CFunctionInfo {
	CVarType* return_type;
	std::string name;
	std::string body;
};
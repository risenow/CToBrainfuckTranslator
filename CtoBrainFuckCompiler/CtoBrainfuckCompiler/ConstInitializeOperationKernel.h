#pragma once
#include <string>
#include "compile_utils.h"
#include "CVar.h"
#include "BFMemoryManagerIntegrator.h"

class BaseTypeConstInitializeOperationKernel {
	BFMemoryManagerIntegrator* memory_manager;
public:
	BaseTypeConstInitializeOperationKernel() {}
	~BaseTypeConstInitializeOperationKernel() {}

	void integrate(BFMemoryManagerIntegrator* _memory_manager) {
		memory_manager = _memory_manager;
	}

	template<typename T>
	std::string kernel(const CVar& v, T const_value) {
		return "";
	}

	template<>
	std::string kernel(const CVar& v, int const_value) {
		std::string result = "";
		result += memory_manager->cmdInsideBlockJumpTo(v.getOffset());
		result += memory_manager->cmdMakeNull();
		if (const_value >= 0)
			result += "+";
		result += memory_manager->cmdInsideBlockJumpTo(v.getOffset() + 1);
		result += memory_manager->cmdMakeNull();
		unsigned int abs_value = abs(const_value);
		for (int i = 0; i < abs_value; i++)
			result += "+";

		return result;
	}
};

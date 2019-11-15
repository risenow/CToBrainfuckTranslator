#pragma once

#include "COperationIntegration.h"

class CVarType;

class UnaryOperationKernel {
protected:
	COperationIntegration integration;
	CVarType* v_type;
public:
	virtual std::string kernel(const CVariableMemoryLocation& v) = 0;
	
	void integrate(const COperationIntegration& _integration) {
		integration = _integration;
	}

	std::string operation_word;
	UnaryOperationKernel() {}
	virtual ~UnaryOperationKernel() {}
};
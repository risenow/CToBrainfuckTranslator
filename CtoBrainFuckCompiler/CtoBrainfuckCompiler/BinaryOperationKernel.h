#pragma once
#include "operation_translation_result.h"
//#include "CVarTypesRegister.h"
#include "COperationIntegration.h"
#include "CVar.h"
#include <string>
//#include "CVarType.h"

class CVarType;

#define MEMORY_MANAGER integration.memory_manager //quick memory manager integrator access
#define TYPES_REGISTER integration.types_register //quick var types register access

class BinaryOperationKernel{
protected:
	COperationIntegration integration;
	CVarType* v1_type;
	CVarType* v2_type;
public:
	virtual std::string inlineIntegrateKernel(const CVar& l_operand, const CVar& r_operand) = 0;

	void integrate(const COperationIntegration& _integration) {
		integration = _integration;
	}

	std::string operation_word;
	BinaryOperationKernel() {};
	virtual ~BinaryOperationKernel() {};
};
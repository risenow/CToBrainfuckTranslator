#pragma once
//#include "BFFunctionIntegration.h"
//#include "CVarTypesRegister.h"
class CVarTypesRegister;
class BFMemoryManagerIntegrator;

struct COperationIntegration{
	BFMemoryManagerIntegrator* memory_manager;
	CVarTypesRegister* types_register;

	COperationIntegration(): memory_manager(nullptr), types_register(nullptr) {
	}
	COperationIntegration(BFMemoryManagerIntegrator* _memory_manager, CVarTypesRegister* _types_register) {
		memory_manager = _memory_manager;
		types_register = types_register;
	}
};

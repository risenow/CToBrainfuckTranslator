#pragma once
#include <vector>
#include "CVar.h"
#include "CVarPrototype.h"
#include "BFMemoryBlock.h"

class CVarTypesRegister;

class BFMemoryBlockBuilder {
public:
	BFMemoryBlockBuilder();
	BFMemoryBlockBuilder(maskloc_t mask);
	BFMemoryBlockBuilder(maskloc_t mask, unsigned int depth);

	void setDepthLevel(unsigned int depth);
	void append(BFMemoryManagerIntegrator* memory_integrator, const CVarPrototype& var_prototype);
	BFMemoryBlock build(BFMemoryManagerIntegrator* memory_integrator);

	void createRegisters(BFMemoryManagerIntegrator* memory_manager_integrator, CVarTypesRegister* types_register);

	//bool getVar(const std::string& name, CVar& var);
	CVar getLastVar();
private:
	maskloc_t mask;
	unsigned int depth;
	bool has_registers;
	size_t total_size;
	std::vector<CVar> vars;
};
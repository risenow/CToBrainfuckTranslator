#pragma once
#include <string>
#include "CVar.h"
#include "c2bf_typedefs.h"
//#include "BFMemoryManagerIntegrator.h"
class BFMemoryManagerIntegrator;

class CVarType;

class CVarPrototype {
public:
	CVarPrototype();
	CVarPrototype(const std::string& name, CVarType* type);

	CVar createCVar(BFMemoryManagerIntegrator* memory_integrator, unsigned int level) const;
	CVar createSubCVar(BFMemoryManagerIntegrator* memory_integrator, maskloc_t base_block_mask, unsigned int memory_offset) const;
	CVar createSubCVar(BFMemoryManagerIntegrator* memory_integrator, maskloc_t base_block_mask, unsigned int depth_level, unsigned int memory_offset) const;
	//std::string createSuperSubCVar(BFMemoryManagerIntegrator* memory_integrator, unsigned int base_memory_offset,)

	CVarType* getType();
private:
	std::string name;
	CVarType* type;
};

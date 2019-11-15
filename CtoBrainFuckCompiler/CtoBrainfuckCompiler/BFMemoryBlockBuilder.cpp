#include "stdafx.h"
#include "BFMemoryBlockBuilder.h"
#include "BFMemoryManagerIntegrator.h"
#include "CVarTypesRegister.h"
#include "CVarType.h"
#include <assert.h>

BFMemoryBlockBuilder::BFMemoryBlockBuilder() {}
BFMemoryBlockBuilder::BFMemoryBlockBuilder(maskloc_t _mask) : mask(_mask) {
	vars = std::vector<CVar>();
}
void BFMemoryBlockBuilder::setDepthLevel(unsigned int _level) {
	depth = _level;
}
void BFMemoryBlockBuilder::append(BFMemoryManagerIntegrator* memory_integrator, const CVarPrototype& var_prototype) {
	unsigned int current_offset = total_size;
	vars.push_back(var_prototype.createSubCVar(memory_integrator, mask, depth, current_offset));
	total_size += vars[vars.size() - 1].getType()->getSize();
}
void BFMemoryBlockBuilder::createRegisters(BFMemoryManagerIntegrator* memory_integrator, CVarTypesRegister* types_regiser) {
	assert(!total_size);
	append(memory_integrator, types_regiser->typeIntPointer()->createCVarPrototype(""));
	append(memory_integrator, types_regiser->typeIntPointer()->createCVarPrototype(""));
	has_registers = true;
}
BFMemoryBlock BFMemoryBlockBuilder::build(BFMemoryManagerIntegrator* memory_integrator) {
	mask = memory_integrator->cmdReserveMaskFor(MaskInfo(total_size, depth));
	return BFMemoryBlock(mask, vars, has_registers);
}

CVar BFMemoryBlockBuilder::getLastVar() {
	assert(vars.size());
	return (vars[vars.size() - 1]);
}
/*bool BFMemoryBlockBuilder::getVar(const std::string& name, CVar& var) {
	for (int i = 0; i < vars.size(); i++) {
		if (vars[i].getName() == name) {
			var = vars[i];
			return true;
		}
	}
	return false;
}*/
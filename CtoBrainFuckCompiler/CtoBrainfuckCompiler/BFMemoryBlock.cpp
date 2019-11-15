#include "stdafx.h"
#include "BFMemoryBlock.h"
#include "BFMemoryManagerIntegrator.h"
#include "CVarType.h"

BFMemoryBlock::BFMemoryBlock():mask(0) {}
BFMemoryBlock::BFMemoryBlock(BFMemoryManagerIntegrator* memory_manager_integrator, std::vector<CVarPrototype>& var_prototypes, unsigned int depth) {
	size_t total_size = 0;
	for (int i = 0; i < var_prototypes.size(); i++)
		total_size += var_prototypes[i].getType()->getSize();
	mask = memory_manager_integrator->cmdReserveMaskFor(MaskInfo(total_size, depth));

	vars.reserve(var_prototypes.size());
	unsigned int offset = 0;
	for (int i = 0; i < var_prototypes.size(); i++) {
		vars[i] = var_prototypes[i].createSubCVar(memory_manager_integrator, mask, offset);
		offset += var_prototypes[i].getType()->getSize();
	}
}
BFMemoryBlock::BFMemoryBlock(maskloc_t _mask, const std::vector<CVar>& _vars, bool _has_registers):mask(_mask), vars(_vars), has_registers(_has_registers) {
}
std::string BFMemoryBlock::integrate(BFMemoryManagerIntegrator* memory_integrator) {
	return memory_integrator->cmdCreate(mask);
}
maskloc_t BFMemoryBlock::getMask() {
	return mask;
}

unsigned int BFMemoryBlock::getTempRegisterOffsetPosition() {
	return vars[TEMP_REGISTER_INDEX].getOffset();
}
unsigned int BFMemoryBlock::getAccumulateRegisterOffsetPosition() {
	return vars[ACCUMULATE_REGISTER_INDEX].getOffset();
}
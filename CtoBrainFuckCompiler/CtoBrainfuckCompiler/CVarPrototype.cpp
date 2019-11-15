#include "stdafx.h"
#include "CVarPrototype.h"
#include "BFMemoryManagerIntegrator.h"

CVarPrototype::CVarPrototype():type(nullptr) {}
CVarPrototype::CVarPrototype(const std::string& _name, CVarType* _type):name(_name), type(_type) {}

CVar CVarPrototype::createCVar(BFMemoryManagerIntegrator* memory_integrator, unsigned int level) const {
	return CVar(memory_integrator, name, type, level);
}
CVar CVarPrototype::createSubCVar(BFMemoryManagerIntegrator* memory_integrator, maskloc_t base_mask, unsigned int memory_offset) const {
	return CVar(memory_integrator, name, type, base_mask, memory_integrator->getMaskLevel(base_mask), memory_offset);
}
CVar CVarPrototype::createSubCVar(BFMemoryManagerIntegrator* memory_integrator, maskloc_t base_mask, unsigned int depth_level, unsigned int memory_offset) const {
	return CVar(memory_integrator, name, type, base_mask, depth_level, memory_offset);
}

CVarType* CVarPrototype::getType() {
	return type;
}
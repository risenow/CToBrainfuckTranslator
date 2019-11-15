#include "stdafx.h"
#include "CVar.h"
#include "CVarType.h"
#include "BFMemoryManagerIntegrator.h"
#include <assert.h>

CVar::CVar() : mask(0), name(""), type(nullptr), members({}), mem_offset(0) {}
CVar::CVar(const std::string& _name, CVarType* _type, const std::vector<CVar>& _members, maskloc_t _mask, unsigned int _level) : name(_name), type(_type), members(_members), mask(_mask), mem_offset(0), level(_level) {}
CVar::CVar(BFMemoryManagerIntegrator* memory_integrator, const std::string& _name, CVarType* _type, unsigned int _level): name(_name), type(_type), level(_level) {
	bool is_base_type = false;

	unsigned int var_members_protypes_count = type->getVarMembersPrototypesCount();
	members.reserve(var_members_protypes_count);

	if (!var_members_protypes_count)
		is_base_type = true;

	//if mem_offset is not setted we need to allocate memory
	mask = memory_integrator->cmdReserveMaskFor(MaskInfo(type->getSize(), level));

	unsigned int temp_mem_offset = 0;
	if (!is_base_type) {
		for (int i = 0; i < var_members_protypes_count; i++) {
			members[i] = type->getVarPrototypeByIndex(i).createSubCVar(memory_integrator, mask, temp_mem_offset);

			temp_mem_offset += members[i].getType()->getSize();
		}
	}
}
CVar::CVar(BFMemoryManagerIntegrator* memory_integrator, const std::string& _name, CVarType* _type, maskloc_t base_mask,  unsigned int _level, unsigned int _mem_offset) : name(_name), type(_type), level(_level), mask(base_mask), mem_offset(_mem_offset) {
	bool is_base_type = false;

	unsigned int var_members_protypes_count = type->getVarMembersPrototypesCount();
	members.reserve(var_members_protypes_count);

	if (!var_members_protypes_count)
		is_base_type = true;

	unsigned int temp_mem_offset = 0;
	if (!is_base_type) {
		for (int i = 0; i < var_members_protypes_count; i++) {
			members[i] = type->getVarPrototypeByIndex(i).createSubCVar(memory_integrator, mask, temp_mem_offset + mem_offset);

			temp_mem_offset += members[i].getType()->getSize();
		}
	}
}
CVar::~CVar() {}

unsigned int CVar::getOffset() const {
	return mem_offset;
}
maskloc_t CVar::getMask() const {
	return mask;
}
std::string CVar::getName() const {
	return name;
}
CVarType* CVar::getType() const {
	return type;
}
CVar CVar::getMemberVarByIndex(unsigned int index) const {
	assert(index >= 0 && index < members.size());
	return members[index];
}
unsigned int CVar::getMembersCount() const {
	return members.size();
}

std::string CVar::integrate(BFMemoryManagerIntegrator* integrator) {
	std::string brainfuck_code;
	bool is_base_type = false;
	
	if (!members.size())
		is_base_type = true;

	//if mem_offset is not setted we need to allocate memory
	if (!mem_offset) {
		brainfuck_code += integrator->cmdCreate(mask);
	}

	unsigned int temp_mem_offset = 0;
	if (!is_base_type) {
		for (int i = 0; i < members.size(); i++) {
			brainfuck_code += members[i].integrate(integrator);
		}
	}

	return brainfuck_code;
}
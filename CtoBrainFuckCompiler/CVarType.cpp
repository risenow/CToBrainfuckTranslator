#include "stdafx.h"
#include "CVarType.h"
#include <assert.h>

CVarType::CVarType(): base_size(0){}
CVarType::~CVarType() {}

void CVarType::setOperations(const COperationsSet& operations_set) {
	operations = operations_set;
}
void CVarType::addMemberPrototype(const CVarPrototype& member_prototype) {
	var_members_prototypes.push_back(member_prototype);
}
void CVarType::setBaseSize(size_t _base_size) {
	base_size = _base_size;
}

unsigned int CVarType::getVarMembersPrototypesCount() {
	return var_members_prototypes.size();
}
CVarPrototype CVarType::getVarPrototypeByIndex(unsigned int index) {
	return var_members_prototypes[index];
}
CVarPrototype CVarType::createCVarPrototype(const std::string& name) {
	return CVarPrototype(name, this);
}
std::string CVarType::getTypeCWord() {
	return type_specificator_word;
}
void CVarType::setTypeWord(const std::string& type_word) {
	type_specificator_word = type_word;
}
size_t CVarType::getSize() {
	assert(base_size && !var_members_prototypes.size()); //base type cannot have members
	if (base_size)
		return base_size;
	size_t temp_size = 0;
	for (int i = 0; i < var_members_prototypes.size(); i++)
		temp_size += var_members_prototypes[i].getType()->getSize();
	return temp_size;
}
COperationsSet CVarType::getOperationsSet() {
	return operations;
}
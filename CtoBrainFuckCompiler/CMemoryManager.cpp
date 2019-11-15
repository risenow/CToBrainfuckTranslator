#include "stdafx.h"
/*#include "CVarType.h"

void CMemoryManager::registerVar(const std::string& var_name, CVarType* type) {
	vars.insert(std::make_pair(var_name, CVariableMemoryLocation(memory_address_space.allocate(type->size).begin(), type->size, local_group_index, type)));
}
unsigned int CMemoryManager::registerStackVarArray(CVarType* type, size_t size) {
	unsigned int first_el_index = stack.size();
	for (int i = 0; i < size; i++)
		stack.push_back(CVariableMemoryLocation(memory_address_space.allocate(type->size).begin(), type->size, local_group_index, type));
	return first_el_index;
}
CVariableMemoryLocation& CMemoryManager::registerStackVar(CVarType* type) {
	stack.push_back(CVariableMemoryLocation(memory_address_space.allocate(type->size).begin(), type->size, local_group_index, type));
	return stack[stack.size() - 1];
}
CVariableMemoryLocation& CMemoryManager::registerCounterVar(CVarType* type) {
	counters.push_back(CVariableMemoryLocation(memory_address_space.allocate(type->size).begin(), type->size, local_group_index, type));
	return counters[counters.size() - 1];
}

CVariableMemoryLocation CMemoryManager::var(const std::string& var_name) {
	return vars[var_name];
}

CVariableMemoryLocation& CMemoryManager::stackVarByAddress(unsigned int address) {
	for (int i = 0; i < stack.size(); i++) {
		if (stack[i].address() == address)
			return stack[i];
	}
	return stack[0];
}
*/
/*CVariableMemoryLocation CMemoryManager::stack_var(unsigned int index) {
	return stack[index];
}
CVariableMemoryLocation CMemoryManager::counter_var(unsigned int index) {
	return counters[index];
}*/
/*
void CMemoryManager::moveVarToUpperGroup(const std::string& var_name) {
	vars[var_name].moveToUpperGroup();
}
void CMemoryManager::moveStackVarToUpperGroup(unsigned int stack_index) {
	stack[stack_index].moveToUpperGroup();
}
void CMemoryManager::moveCounterVarToUpperGroup(unsigned int counter_index) {
	counters[counter_index].moveToUpperGroup();
}

void CMemoryManager::bindStackArrayFirstIndex(unsigned int index) {
	stack_var_array_first_el_index = index;
}
CVariableMemoryLocation& CMemoryManager::stack_var_array_element(unsigned int array_el_index) {
	return stack[stack_var_array_first_el_index + array_el_index];
}

void CMemoryManager::initializeNullCell(CVarType* type_cell) {
	CVariableMemoryLocation null_cell_var = registerStackVar(type_cell);
	null_cell_address = null_cell_var.address();
}
address_t CMemoryManager::getNullCellAddress() {
	return null_cell_address;
}

unsigned int& CMemoryManager::localGroupIndex() {
	return local_group_index;
}

void CMemoryManager::groupFree(unsigned int group_id) {
	std::vector<unsigned int> addresses;
	std::vector<std::string> keys;
	std::map<std::string, CVariableMemoryLocation>::iterator iter = vars.begin();
	
	for (int i = 0; i < vars.size(); i++) {
		if (iter->second.groupID() == group_id) {
			memory_address_space.free(iter->second.getAddressRange());
			keys.push_back(iter->first);
		}
		iter++;
	}
	for (int i = 0; i < keys.size(); i++) {
		vars.erase(keys[i]);
	}
	

	for (int i = 0; i < stack.size(); i++) {
		if (stack[i].groupID() == group_id) {
			memory_address_space.free(stack[i].getAddressRange());
			addresses.push_back(stack[i].address());
		}
	}
	for (int i = 0; i < addresses.size(); i++)
		for (int j = 0; j < stack.size(); j++) {
			if (stack[j].address() == addresses[i])
				stack.erase(stack.begin() + j);
		}
	addresses.clear();

	for (int i = 0; i < counters.size(); i++) {
		if (counters[i].groupID() == group_id) {
			memory_address_space.free(counters[i].getAddressRange());
			addresses.push_back(counters[i].address());
		}
	}
	for (int i = 0; i < addresses.size(); i++)
		for (int j = 0; j < counters.size(); j++) {
			if (counters[j].address() == addresses[i])
				counters.erase(counters.begin() + j);
		}

	memory_address_space.observe_free_memory_address_spaces();
}
void CMemoryManager::localGroupFree() {
	groupFree(local_group_index);
}
unsigned int& CMemoryManager::memoryPosition() {
	return memory_position;
}
CMemoryManager::CMemoryManager(): local_group_index(0), memory_position(0) {
	const unsigned int machine_memory_size = 30000;
	memory_address_space = CMemoryAddressSpace(machine_memory_size);
}
CMemoryManager::~CMemoryManager() {}
*/
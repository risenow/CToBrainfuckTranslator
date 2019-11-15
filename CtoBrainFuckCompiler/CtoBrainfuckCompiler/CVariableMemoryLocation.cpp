#include "stdafx.h"
#include "CVariable.h"
#include "CVarType.h"

CVariableMemoryLocation::CVariableMemoryLocation() {
}
CVariableMemoryLocation::CVariableMemoryLocation(address_t _address, size_t _size, index_t group_id, CVarType* _type): begin_address(_address), memory_size(_size), var_type(_type), group_index(group_id){
}

unsigned int CVariableMemoryLocation::address() const {
	return begin_address;
}
size_t CVariableMemoryLocation::size() const {
	return memory_size;
}
CVarType* CVariableMemoryLocation::type() const {
	return var_type;
}

CMemoryAddressRange CVariableMemoryLocation::getAddressRange() const {
	return CMemoryAddressRange(begin_address, memory_size);
}

unsigned int CVariableMemoryLocation::groupID() const {
	return group_index;
}
void CVariableMemoryLocation::moveToUpperGroup() {
	group_index--;
}
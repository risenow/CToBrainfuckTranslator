#pragma once
#include "variable_type.h"
#include "compile_utils_defs.h"
#include "CMemoryAddressRange.h"

class CVarType;

class CVariableMemoryLocation {
	address_t begin_address;
	address_t memory_size; // deprecated
	index_t  group_index;

	CVarType* var_type;
public:
	CVariableMemoryLocation();
	CVariableMemoryLocation(address_t address, size_t size, index_t group_index, CVarType* type);

	address_t address() const;
	size_t    size() const;
	CVarType* type() const;

	CMemoryAddressRange getAddressRange() const;

	unsigned int groupID() const;
	void moveToUpperGroup();
};

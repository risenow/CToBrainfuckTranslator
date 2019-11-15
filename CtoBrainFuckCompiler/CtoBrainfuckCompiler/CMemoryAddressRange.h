#pragma once
#include "compile_utils_defs.h"

//help structure for memory management
class CMemoryAddressRange {
	address_t begin_address;
	address_t end_address; //exclusive
public:
	CMemoryAddressRange();
	CMemoryAddressRange(address_t begin, size_t size);

	address_t begin() const;
	address_t end() const;
	size_t    size() const;

	CMemoryAddressRange concat(const CMemoryAddressRange& v);
};

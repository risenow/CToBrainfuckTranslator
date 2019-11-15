#include "stdafx.h"
#include "CMemoryAddressRange.h"

CMemoryAddressRange::CMemoryAddressRange(): begin_address(0), end_address(0) {}
CMemoryAddressRange::CMemoryAddressRange(address_t address, size_t size): begin_address(address), end_address(begin_address + size) {}

unsigned int CMemoryAddressRange::begin() const {
	return begin_address;
}
unsigned int CMemoryAddressRange::end() const {
	return end_address;
}
size_t CMemoryAddressRange::size() const {
	return end_address - begin_address;
}

CMemoryAddressRange CMemoryAddressRange::concat(const CMemoryAddressRange& v) {
	return CMemoryAddressRange(begin_address, size() + v.size());
}

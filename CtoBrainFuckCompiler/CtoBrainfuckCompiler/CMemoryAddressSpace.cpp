#include "stdafx.h"
#include <algorithm>
#include "CMemoryAddressSpace.h"

CMemoryAddressSpace::CMemoryAddressSpace() {}
CMemoryAddressSpace::CMemoryAddressSpace(size_t base_memory_size) {
	free_memory.push_back(CMemoryAddressRange(0, base_memory_size));
}

CMemoryAddressRange CMemoryAddressSpace::allocate(size_t size) {
	CMemoryAddressRange result;
	for (int i = 0; i < free_memory.size(); i++)
		if (free_memory[i].size() >= size) {
			result = CMemoryAddressRange(free_memory[i].begin(), size);
			free_memory[i] = CMemoryAddressRange(free_memory[i].begin() + size, free_memory[i].size() - size);
			break;
		}
	return result;
}
void CMemoryAddressSpace::free(const CMemoryAddressRange& address) {
	free_memory.push_back(address);
}
void CMemoryAddressSpace::sort_free_memory_address_spaces() {
	std::sort(free_memory.begin(), free_memory.end(), [](const CMemoryAddressRange& v1, const CMemoryAddressRange& v2)->bool {return (v1.begin() < v2.begin()); });
}
void CMemoryAddressSpace::concat_free_memory_address_spaces() {
	std::vector<CMemoryAddressRange> temp;
	int concat_row_begin_index = 0;
	bool row = false;
	if (free_memory.size() == 1) {
		temp.push_back(free_memory[0]);
		free_memory = temp;
		return;
	}
	for (int i = 0; i < free_memory.size() - 1; i++) {
		if (free_memory[i].end() == free_memory[i + 1].begin()) {
			if (!row) {
				row = true;
				concat_row_begin_index = i;
			}
		}
		else {
			if (row) {
				row = false;
				int concat_row_end_index = i;
				CMemoryAddressRange current_address_range = free_memory[concat_row_begin_index];
				for (int j = concat_row_begin_index; j < concat_row_end_index; j++){
					current_address_range = current_address_range.concat(free_memory[j + 1]);
				}
				temp.push_back(current_address_range);
			}
			else {
				temp.push_back(free_memory[i]);
			}
		}
	}
	if (row) {
		row = false;
		int concat_row_end_index = free_memory.size() - 1;
		CMemoryAddressRange current_address_range = free_memory[concat_row_begin_index];
		for (int j = concat_row_begin_index; j < concat_row_end_index; j++) {
			current_address_range = current_address_range.concat(free_memory[j + 1]);
		}
		temp.push_back(current_address_range);
	}
	else {
		temp.push_back(free_memory[free_memory.size() - 1]);
	}
	free_memory = temp;
}
void CMemoryAddressSpace::clean_free_memory_address_spaces() {
	std::vector<CMemoryAddressRange> temp;
	for (int i = 0; i < free_memory.size(); i++) {
		if (free_memory[i].begin() != free_memory[i].end())
			temp.push_back(free_memory[i]);
	}
	free_memory = temp;
}

void CMemoryAddressSpace::observe_free_memory_address_spaces() {
	sort_free_memory_address_spaces();
	clean_free_memory_address_spaces();
	concat_free_memory_address_spaces();
}
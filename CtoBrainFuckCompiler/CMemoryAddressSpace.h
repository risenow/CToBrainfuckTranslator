#pragma once
#include <vector>
#include "compile_utils_defs.h"
#include "CMemoryAddressRange.h"

//core of memory management
class CMemoryAddressSpace {
	std::vector<CMemoryAddressRange> free_memory;
public:
	CMemoryAddressSpace();
	CMemoryAddressSpace(size_t base_memory_size);

	/*allocate free address range for storing data with needed size
	*/
	CMemoryAddressRange allocate(size_t size);

	/*set address as free for storing data 
	*/
	void free(const CMemoryAddressRange& address);

	/*sorts free memory address ranges from lower to higher
	example: ((0, 1), (3, 4), (1, 3)) -> ((0, 1), (1, 3), (3, 4))
	*/
	void sort_free_memory_address_spaces(); 

	/*deletes false free memory address ranges(begin == end)
	example: ((0, 2), (2, 2), (2, 100)) -> ((0, 2), (2, 100))
	*/
	void clean_free_memory_address_spaces(); 

	/*concatination of neighbor free memory address ranges
	example: ((0, 2), (2,3), (10, 100)) -> ((0, 3), (10, 100))
	*/
	void concat_free_memory_address_spaces(); 

	/*
	1.sort
	2.clean
	3.concat
	*/
	void observe_free_memory_address_spaces();
};
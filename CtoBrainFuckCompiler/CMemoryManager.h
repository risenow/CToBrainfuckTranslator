#pragma once
#include <string>
#include <array>
#include <vector>
#include <map>
#include "compile_utils_defs.h"
#include "CVariable.h"
#include "CMemoryAddressSpace.h"

class CMemoryManager {
	std::map<std::string, CVariableMemoryLocation> vars; //named vars
	std::vector<CVariableMemoryLocation> stack; //unnamed vars
	std::vector<CVariableMemoryLocation> counters; //unnamed vars that can be only unsigned integers

	CMemoryAddressSpace memory_address_space; //memory management core

	address_t memory_position; //current pointer in BF script
	index_t local_group_index; //index of var group working with
	index_t stack_var_array_first_el_index;

	address_t null_cell_address; // address of cell wich value is always null
public:
	/*allocates memory range for storing and access c-variable
	*/
	void registerVar(const std::string& var_name, CVarType* type);

	index_t registerStackVarArray(CVarType* type, size_t size); //return first el index
	CVariableMemoryLocation& registerStackVar(CVarType* type); 

	CVariableMemoryLocation& registerCounterVar(CVarType* type); 

	/*gets a copy CVar object
	*/
	CVariableMemoryLocation var(const std::string& var_name);
	/*provides access to stack var by it's address(searches in stack array)
	*/
	CVariableMemoryLocation& stackVarByAddress(address_t address);

	/*decrement of group_index property of CVar object with name "var_name"
	*/
	void moveVarToUpperGroup(const std::string& var_name);
	/*same with stack var
	*/
	void moveStackVarToUpperGroup(index_t stack_index);
	/*same with counter var
	*/
	void moveCounterVarToUpperGroup(index_t counter_index);

	/*binds index of first stack var index
	it is necessary to call this function before calling <stack_var_array_element> function
	*/
	void bindStackArrayFirstIndex(index_t first_el_index);
	/*binds index (first_el_index(binded by <bindStackArrayFirstIndex>) + array_index)
	*/
	CVariableMemoryLocation& stack_var_array_element(index_t array_index);

	/*registers var(with type = Cell type) that will always be NULL
	this cell is needed for IF mechanism implementation in Brainfuck
	*/
	void initializeNullCell(CVarType* type_cell); // ARGUMENT MUST BE EQUAL CVarTypesRegister::typeCellPointer()
	/*get address of ALWAYS-NULL cell
	*/
	address_t getNullCellAddress();

	index_t& localGroupIndex();

	/*deletes vars with needed index
	 used for clean stack and counter data usually
	*/
	void groupFree(index_t local_group_index);

	/*deletes vars with current index
	*/
	void localGroupFree();

	/*returns reference to memory position to make it possible to change it's value outside the class
	*/
	address_t& memoryPosition();

	CMemoryManager();
	~CMemoryManager();
};

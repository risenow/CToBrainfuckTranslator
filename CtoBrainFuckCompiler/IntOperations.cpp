#include "stdafx.h"
#include "BaseTypesOperations.h"
#include "BFMemoryManagerIntegrator.h"

/*
INT OPERATIONS START
*/
std::string IntPlusOperationKernel::inlineIntegrateKernel(const CVar& v1, const CVar& v2) {
	/*variable_group_index_logic_guard group_id_guard(integration.memory_manager->localGroupIndex());
	std::string result = "";

	CVariableMemoryLocation stack_var = integration.memory_manager->registerStackVar(v1.type());
	integration.memory_manager->stackVarByAddress(stack_var.address()).moveToUpperGroup();

	CVariableMemoryLocation counter_var = integration.memory_manager->registerCounterVar(integration.var_register->typeIntPointer());

	result += cell_to_null(integration.memory_manager, counter_var.address());
	result += cell_to_null(integration.memory_manager, stack_var.address());

	operation_translation_result assign_oper1_result = counter_var.type()->assign_operation->kernel(counter_var, v1);
	operation_translation_result assign_oper2_result = stack_var.type()->assign_operation->kernel(stack_var, v2);

	result += assign_oper1_result.bf_code;
	result += assign_oper2_result.bf_code;
	result += jump_to(integration.memory_manager->memoryPosition(), counter_var.address());
	result += "[";
	result += jump_to(integration.memory_manager->memoryPosition(), stack_var.address());
	result += "+";
	result += jump_to(integration.memory_manager->memoryPosition(), counter_var.address());
	result += "-";
	result += "]";

	integration.memory_manager->localGroupFree();
	return operation_translation_result(result, stack_var.address());*/
	std::string result;
	return result;
}

/*EXPERIMENTAL INT PLUS*/

/*operation_translation_result ExperimentalIntPlusOperationKernel::kernel(const CVariableMemoryLocation& v1, const CVariableMemoryLocation& v2) {
	variable_group_index_logic_guard group_id_guard(integration.memory_manager->localGroupIndex());
	std::string result = "";

	CVariableMemoryLocation stack_var = integration.memory_manager->registerStackVar(v1.type());
	integration.memory_manager->stackVarByAddress(stack_var.address()).moveToUpperGroup();

	CVariableMemoryLocation T1_stack_var = integration.memory_manager->registerStackVar(integration.var_register->typeCellPointer());
	result += cell_to_null(integration.memory_manager, T1_stack_var.address());

	CVariableMemoryLocation T2_stack_var = integration.memory_manager->registerStackVar(integration.var_register->typeCellPointer());
	result += cell_to_null(integration.memory_manager, T2_stack_var.address());

	CVariableMemoryLocation counter_var = integration.memory_manager->registerCounterVar(integration.var_register->typeIntPointer());

	result += cell_to_null(integration.memory_manager, counter_var.address());
	result += cell_to_null(integration.memory_manager, stack_var.address());

	operation_translation_result assign_oper1_result = counter_var.type()->assign_operation->kernel(counter_var, v1);
	operation_translation_result assign_oper2_result = stack_var.type()->assign_operation->kernel(stack_var, v2);

	unsigned int sign1  = get_int_var_sign_cell_address(counter_var);
	unsigned int value1 = get_int_var_value_cell_address(counter_var);

	unsigned int sign2  = get_int_var_sign_cell_address(stack_var);
	unsigned int value2 = get_int_var_value_cell_address(stack_var);

	result += assign_oper1_result.bf_code;
	result += assign_oper2_result.bf_code;
	
	//0
	//code region IF SIGN1 == '+'
	result += jump_to(integration.memory_manager->memoryPosition(), sign1); // 1
	result += "["; //2

	//code region IF SIGN2 == '+'
	result += jump_to(integration.memory_manager->memoryPosition(), sign2); //3
	result += "["; //4
	result += jump_to(integration.memory_manager->memoryPosition(), value1); //5
	result += "+"; //6
	result += jump_to(integration.memory_manager->memoryPosition(), value2); //7
	result += "-"; //8
	result += "]"; //9
	
	//code region IF SIGN2 == '-'
	result += jump_to(integration.memory_manager->memoryPosition(), sign2); //10
	result += "-"; //11
	result += "["; //12
	result += jump_to(integration.memory_manager->memoryPosition(), T1_stack_var.address()); //13
	result += "-"; // 14
	result += jump_to(integration.memory_manager->memoryPosition(), value1); //15
	result += "-"; // 16
	result += "["; // 17
	result += jump_to(integration.memory_manager->memoryPosition(), T1_stack_var.address()); // 18
	result += "+"; // 19
	result += jump_to(integration.memory_manager->memoryPosition(), integration.memory_manager->getNullCellAddress()); // 20
	result += "]"; // 21
	result += jump_to(integration.memory_manager->memoryPosition(), value2); // 22
	result += "-"; // 23
	result += "["; // 24
	result += jump_to(integration.memory_manager->memoryPosition(), T1_stack_var.address()); // 25
	result += "+"; // 26
	result += jump_to(integration.memory_manager->memoryPosition(), integration.memory_manager->getNullCellAddress()); // 27
	result += "]"; // 28
	result += jump_to(integration.memory_manager->memoryPosition(), T1_stack_var.address()); // 29
	result += "["; // 30
	result += "+"; // 31
	result += jump_to(integration.memory_manager->memoryPosition(), integration.memory_manager->getNullCellAddress()); // 32
	result += "]"; // 33
	result += jump_to(integration.memory_manager->memoryPosition(), T1_stack_var.address()); // 34
	result += "]"; // 35
	result += jump_to(integration.memory_manager->memoryPosition(), sign2); // 36

	integration.memory_manager->localGroupFree();
	return operation_translation_result(result, stack_var.address());
}
*/
std::string IntAssignOperationKernel::inlineIntegrateKernel(const CVar& v1, const CVar& v2) {
	std::string result;
	result += MEMORY_MANAGER->cmdInsideBlockCopy(v2.getOffset(), v1.getOffset());
	result += MEMORY_MANAGER->cmdInsideBlockCopy(v2.getOffset(), v1.getOffset());
	return result;
}


/*
INT OPERATIONS END
*/
#include "stdafx.h"
#include "CVarTypesRegister.h"
#include "BaseTypesOperations.h"
#include "COperationIntegration.h"

void CVarTypesRegister::initializeCell(BFMemoryManagerIntegrator* memory_manager) {
	COperationIntegration operation_integration = COperationIntegration(memory_manager, this);
	COperationsSet operations_set;
	operations_set.setBinary(std::make_shared<CellAssignOperationKernel>(), BI_ASSIGN_OPERATION);
	operations_set.setConstAssign(&const_initialize_operation_kernel);
	operations_set.integrate(operation_integration);
	type_cell.setOperations(operations_set);

	type_cell.setTypeWord("");
	type_cell.setBaseSize(1);
}

//deprecated
/*void CVarTypesRegister::initializeInt(BFMemoryManagerIntegrator* memory_manager) {
	COperationIntegration operation_integration = COperationIntegration(memory_manager, this);
	//binary setup
	type_int.plus_operation = new IntPlusOperationKernel();
	type_int.plus_operation->integrate(operation_integration);

	type_int.minus_operation  = nullptr;
	type_int.mult_operation   = nullptr;
	type_int.devide_operation = nullptr;

	type_int.assign_operation = new IntAssignOperationKernel();
	type_int.assign_operation->integrate(operation_integration);

	//unary setup
	type_int.postfix_increment_operation = nullptr;
	type_int.prefix_increment_operation  = nullptr;
	type_int.postfix_decrement_operation = nullptr;
	type_int.prefix_decrement_operation  = nullptr;

	//const init setup
	type_int.const_initialize_operation = &const_initialize_operation_kernel;

	type_int.type_specificator_word = "int";
	type_int.size = 1; 
}*/
void CVarTypesRegister::initializeExperimentalInt(BFMemoryManagerIntegrator* memory_manager) {
	COperationIntegration operation_integration = COperationIntegration(memory_manager, this);
	COperationsSet operations_set;
	operations_set.setBinary(std::make_shared<IntAssignOperationKernel>(), BI_ASSIGN_OPERATION);
	operations_set.setBinary(std::make_shared<IntPlusOperationKernel>(), BI_PLUS_OPERATION);
	operations_set.setConstAssign(&const_initialize_operation_kernel);
	operations_set.integrate(operation_integration);
	type_int.setOperations(operations_set);
	type_int.setBaseSize(2);
	type_int.setTypeWord("int");
}
void CVarTypesRegister::initializeBaseTypes(BFMemoryManagerIntegrator* memory_manager) {
	const_initialize_operation_kernel.integrate(memory_manager);

	initializeExperimentalInt(memory_manager);
	initializeCell(memory_manager);
}
CVarType* CVarTypesRegister::typeByWord(const std::string& word) {
	if (type_int.getTypeCWord() == word)
		return &type_int;
	if (type_char.getTypeCWord() == word)
		return &type_char;
	if (type_float.getTypeCWord() == word)
		return &type_float;
	if (type_double.getTypeCWord() == word)
		return &type_double;
	return &type_int;
}

CVarTypesRegister::CVarTypesRegister() {}
void CVarTypesRegister::initialize(BFMemoryManagerIntegrator* memory_manager) {
	initializeBaseTypes(memory_manager);
}
CVarType* CVarTypesRegister::typeFloatPointer() {
	return &type_float;
}
CVarType* CVarTypesRegister::typeDoublePointer() {
	return &type_double;
}
CVarType* CVarTypesRegister::typeIntPointer() {
	return &type_int;
}
CVarType* CVarTypesRegister::typeCharPointer() {
	return &type_char;
}
CVarType* CVarTypesRegister::typeCellPointer() {
	return &type_cell;
}

std::vector<CVarType*> CVarTypesRegister::getBaseVarTypes() {
	std::vector<CVarType*> var_types(2);
	var_types[0] = &type_int;
	var_types[1] = &type_float;
	return var_types;
}
#include "stdafx.h"
#include "COperationsSet.h"

COperationsSet::COperationsSet() {
}
COperationsSet::~COperationsSet(){
}

void COperationsSet::setBinary(const std::shared_ptr<BinaryOperationKernel>& oper, OperationType type) {
	switch (type)
	{
	case BI_PLUS_OPERATION:
		plus_operation = oper;
		break;
	case BI_MINUS_OPERATION:
		minus_operation = oper;
		break;
	case BI_MULT_OPERATION:
		mult_operation = oper;
		break;
	case BI_DEVIDE_OPERATON:
		devide_operation = oper;
		break;
	default:
		break;
	}
}
void COperationsSet::setUnary(const std::shared_ptr<UnaryOperationKernel>& oper, OperationType type) {
	switch (type)
	{
	case UN_PRE_INC_OPERATION:
		prefix_increment_operation = oper;
		break;
	case UN_POST_INC_OPERATION:
		postfix_increment_operation = oper;
		break;
	case UN_PRE_DEC_OPERATION:
		prefix_decrement_operation = oper;
		break;
	case UN_POST_DEC_OPERATION:
		postfix_decrement_operation = oper;
		break;
	default:
		break;
	}
}
void COperationsSet::setConstAssign(BaseTypeConstInitializeOperationKernel* oper) {
	const_assign_operation = oper;
}

void COperationsSet::integrate(const COperationIntegration& integration){
	if (plus_operation)
		plus_operation->integrate(integration);
	if (minus_operation)
		minus_operation->integrate(integration);
	if (mult_operation)
		mult_operation->integrate(integration);
	if (devide_operation)
		devide_operation->integrate(integration);

	if (prefix_increment_operation)
		prefix_increment_operation->integrate(integration);
	if (postfix_increment_operation)
		postfix_increment_operation->integrate(integration);
	if (prefix_decrement_operation)
		prefix_decrement_operation->integrate(integration);
	if (postfix_decrement_operation)
		postfix_decrement_operation->integrate(integration);
}

BinaryOperationKernel* COperationsSet::getBinary(OperationType type) {
	switch (type)
	{
	case BI_PLUS_OPERATION:
		return plus_operation.get();
		break;
	case BI_MINUS_OPERATION:
		return minus_operation.get();
		break;
	case BI_MULT_OPERATION:
		return mult_operation.get();
		break;
	case BI_DEVIDE_OPERATON:
		return devide_operation.get();
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}
UnaryOperationKernel* COperationsSet::getUnary(OperationType type) {
	switch (type)
	{
	case UN_PRE_INC_OPERATION:
		return prefix_increment_operation.get();
		break;
	case UN_POST_INC_OPERATION:
		return postfix_increment_operation.get();
		break;
	case UN_PRE_DEC_OPERATION:
		return prefix_increment_operation.get();
		break;
	case UN_POST_DEC_OPERATION:
		return postfix_decrement_operation.get();
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}
BaseTypeConstInitializeOperationKernel* COperationsSet::getConstAssign() {
	return const_assign_operation;
}
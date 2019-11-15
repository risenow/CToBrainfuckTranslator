#pragma once
#include "BaseTypesOperations.h"
#include "ConstInitializeOperationKernel.h"
#include <memory>

class COperationsSet {
private:
	template<class T>
	void free_oper(T* oper) {
	}

	BaseTypeConstInitializeOperationKernel* const_assign_operation;

	std::shared_ptr<BinaryOperationKernel> plus_operation;
	std::shared_ptr<BinaryOperationKernel> minus_operation;
	std::shared_ptr<BinaryOperationKernel> devide_operation;
	std::shared_ptr<BinaryOperationKernel> mult_operation;
	std::shared_ptr<BinaryOperationKernel> assign_operation;

	std::shared_ptr<UnaryOperationKernel> prefix_increment_operation;
	std::shared_ptr<UnaryOperationKernel> postfix_increment_operation;
	std::shared_ptr<UnaryOperationKernel> prefix_decrement_operation;
	std::shared_ptr<UnaryOperationKernel> postfix_decrement_operation;
public:
	COperationsSet();

	~COperationsSet();

	void setBinary(const std::shared_ptr<BinaryOperationKernel>& oper_kernel, OperationType type);
	void setUnary (const std::shared_ptr<UnaryOperationKernel>& oper_kernel, OperationType type);
	void setConstAssign(BaseTypeConstInitializeOperationKernel* oper_kernel); //work arround before we'll have have heavy structures with custom const assignation

	void integrate(const COperationIntegration& integration);

	BinaryOperationKernel* getBinary(OperationType type);
	UnaryOperationKernel*  getUnary (OperationType type);
	BaseTypeConstInitializeOperationKernel* getConstAssign();
};

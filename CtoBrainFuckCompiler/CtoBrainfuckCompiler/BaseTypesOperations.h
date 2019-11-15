#pragma once
#include "BinaryOperationKernel.h"
#include "UnaryOperationKernel.h"

enum OperationType { BI_PLUS_OPERATION, BI_MINUS_OPERATION, BI_MULT_OPERATION, BI_DEVIDE_OPERATON, BI_ASSIGN_OPERATION, UN_PRE_INC_OPERATION, UN_POST_INC_OPERATION, UN_PRE_DEC_OPERATION, UN_POST_DEC_OPERATION, CONST_ASSIGN_OPERATION };

//CELL OPERATIONS
//BINARY
class CellAssignOperationKernel : public BinaryOperationKernel {
public:
	virtual std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};

//INT OPERATIONS
//BINARY
class IntPlusOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class ExperimentalIntPlusOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class IntMinusOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class IntMultOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class IntDevideOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class IntAssignOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class ExperimentalIntAssignOperationKernel : public BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
//UNARY
class IntPrefixIncrementOperationKernel : public UnaryOperationKernel {
public:
	std::string kernel(const CVar& v);
};
class IntPostfixIncrementOperationKernel : public UnaryOperationKernel {
public:
	std::string kernel(const CVar& v);
};
class IntPrefixDecrementOperationKernel : public UnaryOperationKernel {
public:
	std::string kernel(const CVar& v);
};
class IntPostfixDecrementOperationKernel : public UnaryOperationKernel {
public:
	std::string kernel(const CVar& v);
};

//FLOAT OPERATIONS
//BINARY
class FloatPlusOperationKernel : BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class FloatMinusOperationKernel : BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class FloatMultOperationKernel : BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class FloatDevideOperationKernel : BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
class FloatAssignOperationKernel : BinaryOperationKernel {
public:
	std::string inlineIntegrateKernel(const CVar& v1, const CVar& v2);
};
//UNARY
class FloatPrefixIncrementOperationKernel : UnaryOperationKernel {
public:
	std::string kernel(const CVar& v, const CVar& v2);
};
class FloatPostfixIncrementOperationKernel : UnaryOperationKernel {
public:
	std::string kernel(const CVar& v, const CVar& v2);
};


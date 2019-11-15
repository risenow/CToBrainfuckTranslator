#pragma once
//#include "BFMemoryManagerIntegrator.h"
#include "CVarType.h"
#include "ConstInitializeOperationKernel.h"

#define OPEN_BASE_VAR_TYPE_NAMES_DECLARATION enum{
#define CLOSE_BASE_VAR_TYPE_NAMES_DECLARATION };

typedef unsigned int enum_t;

class BFMemoryManagerIntegrator;

//manages prototypes of C-types and extended types(struct/class)
class CVarTypesRegister{
	BaseTypeConstInitializeOperationKernel const_initialize_operation_kernel;

	//PROTOTYPES
	/*
	BASE TYPE
	structure
	value[0]

	CAN HAVE ONLY POSITIVE VALUES IN BF MACHINE MEMORY(stack cells are exceptions limited times)
	*/
	CVarType type_cell;

	/*
	FLOAT TYPE
	structure
	sign[0] cell[1] cell[2]
	[0] - sign
	[1] - integer part
	[2] = fract part
	*/
	CVarType type_float;

	/*
	INT TYPE
	structure
	sign[0] cell[1]
	[0] - sign
	[1] - value
	*/
	CVarType type_int;

	/*
	CHAR TYPE
	int structure analog
	*/
	CVarType type_char;

	/*
	DOUBLE TYPE
	float structure analog
	*/
	CVarType type_double;

	//initializers of types prototypes
	void initializeCell(BFMemoryManagerIntegrator* memory_manager);
	void initializeFloat(BFMemoryManagerIntegrator* memory_manager);
	void initializeInt(BFMemoryManagerIntegrator* memory_manager);
	void initializeExperimentalInt(BFMemoryManagerIntegrator* memory_manager);
	void initializeChar(BFMemoryManagerIntegrator* memory_manager);
	void initializeDouble(BFMemoryManagerIntegrator* memory_manager);

	void initializeBaseTypes(BFMemoryManagerIntegrator* memory_manager);
public:
	CVarTypesRegister();

	//initializes all structures
	void initialize(BFMemoryManagerIntegrator* memory_manager);

	OPEN_BASE_VAR_TYPE_NAMES_DECLARATION
		TYPE_FLOAT, TYPE_DOUBLE, TYPE_INT, TYPE_CHAR, TYPE_CELL
	CLOSE_BASE_VAR_TYPE_NAMES_DECLARATION

	//pointers to prototypes
	CVarType* typeFloatPointer();
	CVarType* typeDoublePointer();
	CVarType* typeIntPointer();
	CVarType* typeCharPointer();
	CVarType* typeCellPointer();

	std::vector<CVarType*> getBaseVarTypes();

	bool isBaseType(CVarType* type);
	enum_t getBaseTypeNameEnum(CVarType* type);
	std::string getTypeName(CVarType* type);

	//prototype by c-type specificator(example: "int", "float", etc.)
	CVarType* typeByWord(const std::string& word);
};
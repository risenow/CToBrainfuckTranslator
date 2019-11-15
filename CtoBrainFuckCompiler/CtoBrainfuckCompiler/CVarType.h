#pragma once
#include <string>
#include <vector>
#include "COperationsSet.h"
#include "CVarPrototype.h"

class BinaryOperationKernel;
class UnaryOperationKernel;
class BaseTypeConstInitializeOperationKernel;

class CVarType {
private:
	std::vector<CVarPrototype> var_members_prototypes;
	size_t base_size;

	std::string type_specificator_word;

	COperationsSet operations;
public:
	void setOperations(const COperationsSet& operations);
	void addMemberPrototype(const CVarPrototype& member_prototype);
	void setBaseSize(size_t base_size);
	void setTypeWord(const std::string& c_word);

	unsigned int getVarMembersPrototypesCount();
	CVarPrototype getVarPrototypeByIndex(unsigned int index);

	CVarPrototype createCVarPrototype(const std::string& name);

	std::string getTypeCWord();
	size_t getSize();
	COperationsSet getOperationsSet();

	CVarType();
	~CVarType();
};
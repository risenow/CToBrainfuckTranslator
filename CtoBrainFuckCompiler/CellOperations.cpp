#include "stdafx.h"
#include "BaseTypesOperations.h"
#include "BFMemoryManagerIntegrator.h"

/*
CELL OPERATIONS START
*/
std::string CellAssignOperationKernel::inlineIntegrateKernel(const CVar& v1, const CVar& v2) {
	std::string result;
	result += MEMORY_MANAGER->cmdInsideBlockCopy(v2.getOffset(), v1.getOffset());
	return result;
}
/*
CELL OPERATIONS END
*/
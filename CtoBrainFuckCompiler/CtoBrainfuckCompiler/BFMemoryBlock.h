#pragma once
#include "CVar.h"
#include "CVarPrototype.h"
#include "c2bf_typedefs.h"

#include <vector>
class BFMemoryManagerIntegrator;
class CVarTypesRegister;

constexpr unsigned int TEMP_REGISTER_INDEX = 0;
constexpr unsigned int ACCUMULATE_REGISTER_INDEX = 1;

class BFMemoryBlock {
public:
	BFMemoryBlock();
	BFMemoryBlock(BFMemoryManagerIntegrator* memory_integrator, std::vector<CVarPrototype>& vars_prototypes, unsigned int depth);
	BFMemoryBlock(maskloc_t mask, const std::vector<CVar>& vars, bool has_registers);

	void createLocalRegisters(CVarTypesRegister* types_register);

	std::string integrate(BFMemoryManagerIntegrator* memory_integrator);

	maskloc_t getMask();
	unsigned int getAccumulateRegisterOffsetPosition();
	unsigned int getTempResultRegisterOffsetPosition();
	unsigned int getTempRegisterOffsetPosition();
private:
	bool has_registers;

	maskloc_t mask;
	std::vector<CVar> vars; //offset defined vars
};

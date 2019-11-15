#pragma once
#include <string>
#include <vector>
#include "c2bf_typedefs.h"
//#include "BFMemoryManagerIntegrator.h"
class BFMemoryManagerIntegrator;

class CVarType;

class CVar {
public:
	CVar();
	CVar(const std::string& name, CVarType* type, const std::vector<CVar>& members, maskloc_t mask, unsigned int level);
	CVar(BFMemoryManagerIntegrator* memory_integrator, const std::string& name, CVarType* type, unsigned int level);
	CVar(BFMemoryManagerIntegrator* memory_integrator, const std::string& name, CVarType* type, maskloc_t mask, unsigned int level, unsigned int memory_offset);
	~CVar();

	unsigned int getOffset()                             const;
	maskloc_t    getMask()                               const;
	std::string  getName()                               const;
	CVarType*    getType()                               const;
	CVar         getMemberVarByIndex(unsigned int index) const;

	unsigned int getMembersCount() const;

	std::string integrate(BFMemoryManagerIntegrator* integrator);
private:
	unsigned int mem_offset;
	unsigned int level;

	maskloc_t         mask;
	std::string       name;
	CVarType*         type;
	std::vector<CVar> members;
};
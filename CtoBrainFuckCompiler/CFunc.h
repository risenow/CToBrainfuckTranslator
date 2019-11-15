#pragma once
#include <string>
#include <vector>
#include "CVarPrototype.h"
#include "CVar.h"
#include "BFMemoryManagerIntegrator.h"

class CFunc {
public:
	CFunc();
	CFunc(const std::string& name, const std::string& arg_str, const std::string& body_str, CVarType* result_type);
	
	std::string getName();

	void parse(const std::string& cfunc_code);
	std::string integrate(BFMemoryManagerIntegrator* memory_integrator);
private:
	std::string name;

	CVar function_invoker;
	CVar result;
	std::vector<CVar> local_vars;
	std::vector<CVar> parameters;
};
#pragma once
#include <vector>
#include "CFunc.h"
#include "CVar.h"
#include "CVarType.h"

class CScope {
public:
	CScope();

	void addType(CVarType* type);
	void addVar(const CVar& var);
	void addFunc(const CFunc& func);

	void addTypes(const std::vector<CVarType*>& types);
	void addVars (const std::vector<CVar>& vars);
	void addFuncs(const std::vector<CFunc>& funcs);

	bool getType(const std::string& name, CVarType*& type);
	bool getVar(const std::string& name, CVar& var);
	bool getFunc(const std::string& name, CFunc& func);

	CScope concat(const CScope& scope);
private:
	std::vector<CVarType*> types;
	std::vector<CVar> vars;
	std::vector<CFunc> funcs;
};
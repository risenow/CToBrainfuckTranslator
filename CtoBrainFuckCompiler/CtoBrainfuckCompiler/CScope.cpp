#include "stdafx.h"
#include "CScope.h"
#include <assert.h>

CScope::CScope(){ }

void CScope::addVar(const CVar& var) {
	vars.push_back(var);
}
void CScope::addType(CVarType* type) {
	types.push_back(type);
}
void CScope::addFunc(const CFunc& func) {
	funcs.push_back(func);
}

void CScope::addVars(const std::vector<CVar>& _vars) {
	vars.insert(vars.end(), _vars.begin(), _vars.end());
}
void CScope::addTypes(const std::vector<CVarType*>& _types){
	types.insert(types.end(), _types.begin(), _types.end());
}
void CScope::addFuncs(const std::vector<CFunc>& _funcs) {
	funcs.insert(funcs.end(), _funcs.begin(), _funcs.end());
}

bool CScope::getVar(const std::string& name, CVar& var) {
	for (int i = 0; i < vars.size(); i++)
		if (vars[i].getName() == name) {
			var = vars[i];
			return true;
		}
	return false;
}
bool CScope::getType(const std::string& name, CVarType*& type) {
	for (int i = 0; i < types.size(); i++)
		if (types[i]->getTypeCWord() == name) {
			type = types[i];
			return true;
		}
	return false;
}
bool CScope::getFunc(const std::string& name, CFunc& func) {
	for (int i = 0; i < funcs.size(); i++)
		if (funcs[i].getName() == name) {
			func = funcs[i];
			return true;
		}
	return false;
}

CScope CScope::concat(const CScope& scope) {
	CScope result;

	result.addVars(vars);
	result.addVars(scope.vars);
	
	result.addFuncs(funcs);
	result.addFuncs(scope.funcs);

	result.addTypes(types);
	result.addTypes(scope.types);

	return result;
}
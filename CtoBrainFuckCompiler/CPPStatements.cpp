#include "stdafx.h"
#include "CPPStatements.h"

//**** CPPType
CPPType::CPPType() {}
CPPType::CPPType(const std::string& _type_id) : type_id(_type_id) {}
std::string CPPType::getID() {
	return type_id;
}

//**** CPPStatement
CPPStatement::CPPStatement() : type(CPP_NONE) {}
CPPStatement::CPPStatement(const std::vector<CPPStatement*>& _childs) : type(CPP_NONE), childs(_childs) {
}
CPPStatement::CPPStatement(CPPStatementType _type) : type(_type) {}
CPPStatementType CPPStatement::getType() {
	return type;
}

//**** CPPVariableDeclarationStatement
CPPVariableDeclarationStatement::CPPVariableDeclarationStatement() : CPPStatement(CPP_VARIABLE_DECLARATION) {}
CPPVariableDeclarationStatement::CPPVariableDeclarationStatement(const CPPType& _cpp_type, const std::string& _id) : CPPStatement(CPP_VARIABLE_DECLARATION), cpp_type(_cpp_type), id(_id) {}
CPPType CPPVariableDeclarationStatement::getCPPType() {
	return cpp_type;
}
std::string CPPVariableDeclarationStatement::getID() {
	return id;
}

//**** CPPFunctionArgumentsStatement
CPPFunctionArgumentsStatement::CPPFunctionArgumentsStatement() : CPPStatement(CPP_FUNCTION_ARGUMENTS) {}
CPPFunctionArgumentsStatement::CPPFunctionArgumentsStatement(const std::vector<CPPVariableDeclarationStatement*>& args_decls) : CPPStatement(CPP_FUNCTION_ARGUMENTS), arguments(args_decls) {
	childs.resize(args_decls.size());
	for (int i = 0; i < childs.size(); i++) {
		childs[i] = (CPPStatement*)args_decls[i];
	}
}
std::vector<CPPVariableDeclarationStatement*> CPPFunctionArgumentsStatement::getArguments() {
	return arguments;
}

//**** CPPFunctionDeclarationStatement
CPPFunctionDeclarationStatement::CPPFunctionDeclarationStatement() : CPPStatement(CPP_FUNCTION_DECLARATION) {}
CPPFunctionDeclarationStatement::CPPFunctionDeclarationStatement(const CPPType& _return_type, const std::string& _id, CPPFunctionArgumentsStatement* arguments_statement) : CPPStatement(CPP_FUNCTION_DECLARATION), return_type(_return_type), id(_id), arguments(arguments_statement) {
	childs.push_back((CPPStatement*)arguments_statement);
}
CPPType CPPFunctionDeclarationStatement::getReturnType() {
	return return_type;
}
CPPFunctionArgumentsStatement* CPPFunctionDeclarationStatement::getArgumentsStatement() {
	return arguments;
}
std::string CPPFunctionDeclarationStatement::getID() {
	return id;
}

//**** CPPBodyStatement
CPPBodyStatement::CPPBodyStatement() : CPPStatement(CPP_BODY) {}
CPPBodyStatement::CPPBodyStatement(const std::vector<CPPStatement*>& statements) : CPPStatement(CPP_BODY), statement_sequence(statements) {
	childs.insert(childs.begin(), statements.begin(), statements.end());
}
std::vector<CPPStatement*> CPPBodyStatement::getSatementSequence() {
	return statement_sequence;
}

//**** CPPFunctionDefinitionStatement
CPPFunctionDefinitionStatement::CPPFunctionDefinitionStatement() : CPPStatement(CPP_FUNCTION_DEFINITION) {}
CPPFunctionDefinitionStatement::CPPFunctionDefinitionStatement(CPPFunctionDeclarationStatement* _declaration_statement, CPPBodyStatement* _body_statement) : CPPStatement(CPP_FUNCTION_DEFINITION), declaration_statement(_declaration_statement), body_statement(_body_statement) {
	childs.push_back((CPPStatement*)_declaration_statement);
	childs.push_back((CPPStatement*)_body_statement);
}
CPPBodyStatement* CPPFunctionDefinitionStatement::getBodyStatement() {
	return body_statement;
}
CPPFunctionDeclarationStatement* CPPFunctionDefinitionStatement::getDeclarationStatement(){
	return declaration_statement;
}

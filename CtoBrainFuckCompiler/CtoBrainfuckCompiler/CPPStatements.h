#pragma once
#include <vector>
#include <string>

enum CPPStatementType {
	CPP_FUNCTION_DECLARATION,
	CPP_FUNCTION_DEFINITION,
	CPP_VARIABLE_DECLARATION,
	CPP_FUNCTION_ARGUMENTS,
	CPP_BODY,
	CPP_ASSIGN,
	CPP_NONE
};

class CPPType {
public:
	CPPType();
	CPPType(const std::string& type_id);

	std::string getID();
private:
	std::string type_id;
};

class CPPStatement {
public:
	CPPStatement();
	explicit CPPStatement(CPPStatementType type);
	CPPStatement(const std::vector<CPPStatement*>& childs);

	CPPStatementType getType();
protected:
	std::vector<CPPStatement*> childs;
	CPPStatementType type;
};

class CPPVariableDeclarationStatement : public CPPStatement {
public:
	CPPVariableDeclarationStatement();
	CPPVariableDeclarationStatement(const CPPType& cpp_type, const std::string& id);

	CPPType getCPPType();
	std::string getID();
private:
	CPPType cpp_type;
	std::string id;
};

class CPPFunctionArgumentsStatement : public CPPStatement {
public:
	CPPFunctionArgumentsStatement();
	CPPFunctionArgumentsStatement(const std::vector<CPPVariableDeclarationStatement*>& arguments_decls);

	std::vector<CPPVariableDeclarationStatement*> getArguments();
private:
	std::vector<CPPVariableDeclarationStatement*> arguments;
};

class CPPFunctionDeclarationStatement: public CPPStatement {
public:
	CPPFunctionDeclarationStatement();
	CPPFunctionDeclarationStatement(const CPPType& _return_type, const std::string& id, CPPFunctionArgumentsStatement* arguments_statement);

	CPPType getReturnType();
	CPPFunctionArgumentsStatement* getArgumentsStatement();
	std::string getID();
private:
	CPPType return_type;
	CPPFunctionArgumentsStatement* arguments;
	std::string id;
};

class CPPBodyStatement : public CPPStatement {
public:
	CPPBodyStatement();
	CPPBodyStatement(const std::vector<CPPStatement*>& statement_sequence);

	std::vector<CPPStatement*> getSatementSequence();
private:
	std::vector<CPPStatement*> statement_sequence;
};

class CPPFunctionDefinitionStatement : public CPPStatement {
public:
	CPPFunctionDefinitionStatement();
	CPPFunctionDefinitionStatement(CPPFunctionDeclarationStatement* _declaration_statement, CPPBodyStatement* _body_statement);

	CPPBodyStatement* getBodyStatement();
	CPPFunctionDeclarationStatement* getDeclarationStatement();
private:
	CPPFunctionDeclarationStatement* declaration_statement;
	CPPBodyStatement* body_statement;
};


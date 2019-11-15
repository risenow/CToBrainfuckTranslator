#pragma once

#include <string>
#include <vector>
#include "CPPStatements.h"
#include "TokenWord.h"

#define INC_WORD_INDEX if (m_WordIndex>= m_TokenWords.size()) return; m_WordIndex++; if(m_WordIndex >= m_TokenWords.size()) return
#define DEC_WORD_INDEX if (m_WordIndex <= 0) return; m_WordIndex--
#define PREV_WORD m_TokenWords[m_WordIndex - 1]
#define NEXT_WORD m_TokenWords[m_WordIndex + 1]
#define CUR_WORD m_TokenWords[m_WordIndex]

constexpr unsigned int OPERATOR_WORD_COUNT = 3;
constexpr unsigned int OPERATOR_SYMBS_COUNT = 3;
const char OperatorSymbols[] = { '-', '+', '=' };
const std::string OperatorWords[] = { "-", "+", "="};

constexpr unsigned int SYNTAX_OPERATOR_SYMBS_COUNT = 3;
const char SyntaxOperatorSymbols[] = { '(', ')', ';' };

class CPPAbstractSyntaxTree {
public:
	CPPAbstractSyntaxTree();

	void BuildFrom(const std::string& code);
private:
	void InitBaseTypes();
	void DecomposeIntoWords(const std::string& code);

	bool IsOperatorSymbol(char symb);
	bool IsSyntaxOperatorSymbol(char symb);

	void GatherFunctionDecls(std::vector<CPPFunctionDeclarationStatement*>& dest);
	void GatherVariableDecls(std::vector<CPPVariableDeclarationStatement*>& dest);
	
	bool FindVarDeclByID(const std::string& id, CPPVariableDeclarationStatement*& var_decl);
	bool FindFuncDeclByID(const std::string& id, CPPFunctionDeclarationStatement*& func_decl);
	bool FindTypeByID(const std::string& id, CPPType& type);

	bool IsUnknownIdentifier(const std::string& id);

	//branchs

	//decl branch
	void DeclBranch();
	void FuncDeclBranch();
	void FuncParamsDeclBranch();
	void FuncParamDeclBranch();
	void VarDeclBranch();

	void IdentifierOperandBranch();

	unsigned int m_WordIndex;
	
	std::vector<CPPVariableDeclarationStatement*> m_TempFuncParamsDecls;
	CPPType m_TempType;
	std::string m_TempID;

	std::vector<CPPFunctionDeclarationStatement*> m_GatheredFunctionDecls;
	std::vector<CPPVariableDeclarationStatement*> m_GatheredVariableDecls;

	std::vector<CPPType> m_Types;
	std::vector<CPPStatement*> m_Statements;

	std::vector<TokenWord> m_TokenWords;
};
#include "stdafx.h"
#include "CPPAbstractSyntaxTree.h"

CPPAbstractSyntaxTree::CPPAbstractSyntaxTree() : m_WordIndex(0) 
{
	InitBaseTypes();
}

void CPPAbstractSyntaxTree::BuildFrom(const std::string& cppCode) 
{
	DecomposeIntoWords(cppCode);

	CPPType foundType;
	CPPVariableDeclarationStatement* foundVarDecl;
	CPPFunctionDeclarationStatement* foundFuncDecl;

	std::vector<CPPType> localTypes;
	std::vector<std::string> localUnknownIdentifiers;

	while (m_WordIndex < m_TokenWords.size()) 
	{
		DeclBranch();
		INC_WORD_INDEX;
	}	
}

void CPPAbstractSyntaxTree::FuncParamDeclBranch() 
{
	CPPType localTempType;
	if (FindTypeByID(m_TokenWords[m_WordIndex].word, localTempType))
	{
		INC_WORD_INDEX;
		if (IsUnknownIdentifier(m_TokenWords[m_WordIndex].word)) 
		{
			m_TempFuncParamsDecls.push_back(new CPPVariableDeclarationStatement(localTempType, m_TokenWords[m_WordIndex].word));
		}
	}
}

void CPPAbstractSyntaxTree::FuncParamsDeclBranch() 
{
	while (m_TokenWords[m_WordIndex].word != ")") 
	{
		FuncParamDeclBranch();
		INC_WORD_INDEX;
		if (m_TokenWords[m_WordIndex].word == ",")
			m_WordIndex++;
	}
}

void CPPAbstractSyntaxTree::FuncDeclBranch() {
	if (m_TokenWords[m_WordIndex].word == "(") 
	{
		FuncParamsDeclBranch();
	}
	else
		return;

	INC_WORD_INDEX;

	if (m_TokenWords[m_WordIndex].word == ";" || m_TokenWords[m_WordIndex].word == "{") 
	{
		m_Statements.push_back(new CPPFunctionDeclarationStatement(m_TempType, m_TempID, new CPPFunctionArgumentsStatement(m_TempFuncParamsDecls)));
	}
}

void CPPAbstractSyntaxTree::VarDeclBranch() 
{
	if (m_TokenWords[m_WordIndex].word == ";") 
	{
		m_Statements.push_back(new CPPVariableDeclarationStatement(m_TempType, m_TempID));
	}
	if (m_TokenWords[m_WordIndex].word == "=") 
	{
		m_Statements.push_back(new CPPVariableDeclarationStatement(m_TempType, m_TempID));
	}
}

void CPPAbstractSyntaxTree::DeclBranch() 
{
	CPPType type;
	if (FindTypeByID(m_TokenWords[m_WordIndex].word, type)) 
	{
		m_TempType = type;
		INC_WORD_INDEX;

		if (IsUnknownIdentifier(m_TokenWords[m_WordIndex].word)) 
		{
			m_TempID = m_TokenWords[m_WordIndex].word;
			INC_WORD_INDEX;
			FuncDeclBranch();
			VarDeclBranch();
		}
	}
}



bool CPPAbstractSyntaxTree::IsOperatorSymbol(char symb) 
{
	for (int i = 0; i < OPERATOR_SYMBS_COUNT; i++)
	{
		if (symb == OperatorSymbols[i])
			return true;
	}
	return false;
}

bool CPPAbstractSyntaxTree::IsSyntaxOperatorSymbol(char symb) 
{
	for (int i = 0; i < SYNTAX_OPERATOR_SYMBS_COUNT; i++)
	{
		if (symb == SyntaxOperatorSymbols[i])
			return true;
	}
	return false;
}

void CPPAbstractSyntaxTree::DecomposeIntoWords(const std::string& code) 
{
	unsigned int currentCharIndex = 0;
	std::string tempWord;
	std::string tempOpWord;
	bool isOperatorWord = false;
	
	for (int i = 0; i < code.size(); i++) 
	{
		bool tempWordCanBePushedIntoTokenWords = false;

		if (code[i] == ' ')
			continue;
		
		if (IsSyntaxOperatorSymbol(code[i])) 
		{
			tempWord.push_back(code[i]);
			tempWordCanBePushedIntoTokenWords = true;
		}
		
		if (!tempWordCanBePushedIntoTokenWords)
			tempWord += code[i];

		if (!tempWordCanBePushedIntoTokenWords &&
			i == (code.size() - 1)) 
		{
			tempWordCanBePushedIntoTokenWords = true;
		}

		char nextChar = code[i + 1];
		bool nextCharIsOperatorSymbol = IsOperatorSymbol(nextChar);
		if (!tempWordCanBePushedIntoTokenWords &&
			!isOperatorWord &&
			(nextChar == ' ' || nextCharIsOperatorSymbol)) 
		{
			tempWordCanBePushedIntoTokenWords = true;
			if (nextCharIsOperatorSymbol)
				isOperatorWord = true;
		}
		if (!tempWordCanBePushedIntoTokenWords &&
			isOperatorWord &&
			(nextChar == ' ' || !nextCharIsOperatorSymbol))
		{
			tempWordCanBePushedIntoTokenWords = true;
			isOperatorWord = false;
		}

		if (!tempWordCanBePushedIntoTokenWords &&
			IsSyntaxOperatorSymbol(nextChar))
		{
			tempWordCanBePushedIntoTokenWords = true;
			isOperatorWord = false;
		}

		if (tempWordCanBePushedIntoTokenWords)
		{
			m_TokenWords.push_back(TokenWord(tempWord));
			tempWord = "";
		}

	}
}

void CPPAbstractSyntaxTree::GatherFunctionDecls(std::vector<CPPFunctionDeclarationStatement*>& dest) 
{
	for (int i = 0; i < m_Statements.size(); i++) 
	{
		if (m_Statements[i]->getType() == CPP_FUNCTION_DECLARATION)
			dest.push_back((CPPFunctionDeclarationStatement*)m_Statements[i]);
	}
}

void CPPAbstractSyntaxTree::GatherVariableDecls(std::vector<CPPVariableDeclarationStatement*>& dest) 
{
	for (int i = 0; i < m_Statements.size(); i++) 
	{
		if (m_Statements[i]->getType() == CPP_VARIABLE_DECLARATION)
			dest.push_back((CPPVariableDeclarationStatement*)m_Statements[i]);
	}
}

bool CPPAbstractSyntaxTree::FindFuncDeclByID(const std::string& id, CPPFunctionDeclarationStatement*& funcDecl) 
{
	for (int i = 0; i < m_GatheredFunctionDecls.size(); i++) 
	{
		if (m_GatheredFunctionDecls[i]->getID() == id) 
		{
			funcDecl = m_GatheredFunctionDecls[i];
			return true;
		}
	}
	return false;
}

bool CPPAbstractSyntaxTree::IsUnknownIdentifier(const std::string& id) 
{
	CPPFunctionDeclarationStatement* tempFuncDecl;
	CPPVariableDeclarationStatement* tempVarDecl;
	CPPType localTempType;

	return (!FindFuncDeclByID(id, tempFuncDecl) &&
		!FindVarDeclByID(id, tempVarDecl) &&
		!FindTypeByID(id, localTempType));
}

bool CPPAbstractSyntaxTree::FindVarDeclByID(const std::string& id, CPPVariableDeclarationStatement*& varDecl) 
{
	for (int i = 0; i < m_GatheredVariableDecls.size(); i++) 
	{
		if (m_GatheredVariableDecls[i]->getID() == id) 
		{
			varDecl = m_GatheredVariableDecls[i];
			return true;
		}
	}
	return false;
}

bool CPPAbstractSyntaxTree::FindTypeByID(const std::string& id, CPPType& type) {
	for (int i = 0; i < m_Types.size(); i++) 
	{
		if (m_Types[i].getID() == id) 
		{
			type = m_Types[i];
			return true;
		}
	}
	return false;
}

void CPPAbstractSyntaxTree::InitBaseTypes() 
{
	m_Types.push_back(CPPType("int"));
}

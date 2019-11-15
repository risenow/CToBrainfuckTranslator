// CtoBrainfuckCompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>
//#include "CtoBrainfuckTranslator.h"
#include "CCode.h"

int main()
{
	std::string brainfuck_code = CCode("int i=4;int j=5;int bf=6;").translate();//.translate_debug("int i = 4;int j = 5;int k = i + j;", {"k"});
	std::ofstream file("out.bf", std::ios_base::out | std::ios_base::trunc);
	file << brainfuck_code << std::endl;
	file.close();
	std::cout << brainfuck_code << std::endl;
	_getch();
    return 0;
}


// GenerateBFJumperFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "BFDynamicMemoryJumper.h"

typedef int memloc_t;

std::string forward_jump(size_t cells_count) {
	std::string result;
	for (int i = 0; i < cells_count; i++)
		result += ">";
	return result;
}
std::string back_jump(size_t cells_count) {
	std::string result;
	for (int i = 0; i < cells_count; i++)
		result += "<";
	return result;
}
//start and end are exclusive or inclusive?
std::string generate_jumper(memloc_t start, memloc_t end) {
	std::string result;
	result += ">"; //to 1c("jump to" address stored here)
	for (int i = 0; i < start; i++)
		result += "-";
	result += "<"; //to 0c
	for (int i = start; i < end; i++) {
		//0c (always equal to NULL(0))
		result += ">>"; //to 2c
		result += "["; // if 2c!=0 

		result += "<"; //to 1c("jump to" address stored here)
		result += "-"; 
		
		result += "["; // if 1c != 0
		result += ">"; //to 2c
		result += "-"; //make it null(initial value is -1) //for test initial value = 1
		result += "]"; //endif

		result += "<[<]"; //to 0c
		result += ">>"; //jump to 2c

		result += "["; //if 2c != 0
		result += forward_jump((int)std::fmaxf((float)(i - 2), (float)0)); // 2 or 3?
		result += "#"; //this char points that here will be placed code that works with found cell
		result += back_jump((int)std::fmaxf((float)(i - 2), (float)0)); //to 2c
		result += "-"; //2c to 0 to exit from loop
		result += "]"; //endif

		result += "+"; //2c recover flag to 1
		result += "<<"; // back to 0c

		result += "]"; //endif
	}
	return result;
}

int main()
{
	int c;
	std::string result = generate_jumper(0, 30);
	std::ofstream file("jumper_template.bft", std::ios_base::out | std::ios_base::trunc);
	file << result;
	file.close();
	std::cout << result;
	std::ofstream file_test("jumper_test.bft", std::ios_base::out | std::ios_base::trunc);
	file_test << BFDynamicMemoryJumper("jumper_template.bft").jump("++++");
	file_test.close();
	std::cin >> c;
    return 0;
}


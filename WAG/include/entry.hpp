#pragma once
//This file can only be inclluded in the executable that uses WAG
//Cannot be included in dll's or other shit
#include "WAG.hpp"
int main(int argc, char* argv[]) {
	std::cout << "Test" << std::endl;
	WAG* w = new WAG();
	delete w;
	return 0;
}
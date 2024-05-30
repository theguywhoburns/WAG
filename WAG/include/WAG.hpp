#pragma once

#include <iostream>

#ifdef WAGEXPORTS
#define WAG_API __declspec(dllexport)
#else
#define WAG_API __declspec(dllimport)
#endif

class WAG_API WAG	{
public:
	WAG();
	~WAG() = default;
};
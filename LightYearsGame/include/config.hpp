#pragma once

#include<string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else 
	return "C:/lightyears_fix/LightYearsGame/assets/";
#endif
}

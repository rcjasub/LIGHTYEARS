#pragma once

#include<string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else 
	return "C:/LIGHTYEARS/LightYearsGame/assets/";
#endif
}

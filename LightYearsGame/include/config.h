#pragma once

#include<string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else 
	return "/tmp/jocsan_lightyears/LightYearsGame/assets/";
#endif
}

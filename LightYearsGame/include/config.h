#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "/my_source_code/LightYears/LightYearsGame/assets/";
#endif
}

#include "EntryPoint.h"
#include "Application.hpp"

int main()
{
	ly::Application* app = GetApplication();
	app->Run();
	delete app;
}

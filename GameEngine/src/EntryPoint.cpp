#include"EntryPoint.hpp"
#include"framework/application.hpp"

int main() 
{
	ly::Application* app = GetApplication();
	app->Run();
	delete app;
}
#include "Application.h"
#include <iostream>



void Application::Setup() 
{
	std::cout << "Application::Setup()" << std::endl;
}

void Application::Update() 
{
	std::cout << "Application::Update()" << std::endl;

}

void Application::Draw() 
{
	std::cout << "Application::Draw()" << std::endl;
}

void Application::Keyboard() 
{
	std::cout << "Application::Keyboard()" << std::endl;
}
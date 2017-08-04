#pragma once

#include "Application.h"

Application::Application() { }
Application::~Application() { }


void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Triangle Example");
}

void Application::update()
{
}

void Application::render()
{
}

void Application::cleanup()
{

}

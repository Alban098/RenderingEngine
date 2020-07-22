#pragma once
#include "Application.h"

#ifdef PLATFORM_WINDOWS

extern Engine::Application* Engine::createApplication();

int main(int argc, char** argv)
{
	auto* app = Engine::createApplication();
	app->run();
	delete app;
}

#endif
#pragma once

#ifdef PLATFORM_WINDOWS

extern Engine::Application* Engine::create_application();

int main(int argc, char** argv)
{
	Engine::Log::init();
	ENGINE_INFO("Initialized App");
	
	auto* app = Engine::create_application();
	app->run();
	delete app;
}

#endif
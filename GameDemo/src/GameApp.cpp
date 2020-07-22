#include <Engine.h>

class GameApp : public Engine::Application
{
public:
	GameApp()
	{
		
	}

	~GameApp()
	{
		
	}
};

Engine::Application* Engine::create_application()
{
	return new GameApp();
}
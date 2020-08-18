#include <Engine.h>

class GameLayer : public Engine::Layer
{
public:
	GameLayer()
		: Layer("Game")
	{
	}

	void onUpdate() override
	{
		ENGINE_INFO("GameLayer : Updated");
	}

	void onEvent(Engine::Event& t_event) override
	{
		ENGINE_TRACE("{0}", t_event);
 	}
};

class GameApp : public Engine::Application
{
public:
	GameApp()
	{
		pushLayer(new GameLayer());
		pushOverlay(new Engine::ImGuiLayer());
	}

	~GameApp()
	{
		
	}
};

Engine::Application* Engine::create_application()
{
	return new GameApp();
}
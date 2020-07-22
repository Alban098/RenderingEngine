#pragma once

#include "Core.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//Client defined
	Application* create_application();

}


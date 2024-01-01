#pragma once

#include <SFML/Graphics.hpp>

#include "game_context.hpp"
#include "scene_manager.hpp"

namespace game_infrastructure
{
	class game
	{
	public:
		game();
		void run();
		
	private:
		std::shared_ptr<sf::RenderWindow>  window;
		game_context                       context;
		rendering::scene_manager           scene_manager;
	};
}

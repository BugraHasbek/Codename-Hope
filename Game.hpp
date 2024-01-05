#pragma once

#include <SFML/Graphics.hpp>

#include "game_context.hpp"
#include "scene_manager.hpp"
#include "view_manager.hpp"

namespace game_infrastructure
{
	constexpr bool map_edit_allowed = false;

	class game
	{
	public:
		game();
		void run();
		
	private:
		game_context                       context;
		sf::RenderWindow                   window;
		rendering::scene_manager           scene_manager;
		rendering::view_manager            view_manager;
	};
}

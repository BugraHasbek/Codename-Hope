#pragma once
#include <SFML/Graphics.hpp>

namespace game_infrastructure
{

	using game_settings = struct {
		sf::Vector2u screen_resolution;
	};

	class game_context {
	public:
		game_context();
		sf::Vector2u get_screen_resolution() const { return settings.screen_resolution; }

	private:
		game_settings settings;
	};

}

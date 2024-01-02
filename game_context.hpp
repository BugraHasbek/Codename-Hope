#pragma once
#include <SFML/Graphics.hpp>

namespace game_infrastructure
{
	const     std::string  filename = "context.dat";

	using game_settings = struct {
		sf::Vector2u screen_resolution;
		sf::Vector2f view_center;
	};

	class game_context {
	public:
		game_context();
		sf::Vector2u get_screen_resolution() const { return settings.screen_resolution; }
		sf::Vector2f get_view_center() const { return settings.view_center; }
		void         set_view_center(sf::Vector2f center) { settings.view_center = center; }
		void         write_context() const;
	private:
		game_settings settings;

		void         read_context();
	};

}

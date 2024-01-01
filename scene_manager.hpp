#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "game_context.hpp"

namespace rendering
{
	constexpr unsigned int world_size_x = 100;
	constexpr unsigned int world_size_y = 100;

	class scene_manager {
	public:
		explicit scene_manager();
		void draw(const std::shared_ptr<sf::RenderWindow>& window, const game_infrastructure::game_context& context);

	private:
		sf::Texture empty_texture;
		sf::Texture green_texture;
		sf::Texture invalid_texture;
		std::array<unsigned int, world_size_x* world_size_y> isometric_world;

		std::pair<float, float> world2Screen(const unsigned int& x, const unsigned int& y) const;
	};
}
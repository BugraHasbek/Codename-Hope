#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "game_context.hpp"

namespace rendering
{
	constexpr unsigned int world_size_x  = 20;
	constexpr unsigned int world_size_y  = 20;
	constexpr unsigned int tileset_count = 2;
	const     std::string  filename      = "map.dat";

	class scene_manager {
	public:
		explicit scene_manager(const game_infrastructure::game_context& context);
		void draw(sf::RenderWindow& window);
		void edit_tile(sf::Vector2i mouse_pos, sf::Vector2f top_left_corner);
		void write_tiles() const;
	private:
		game_infrastructure::game_context context;
		sf::Texture empty_texture;
		sf::Texture green_texture;
		sf::Texture invalid_texture;
		std::array<unsigned int, world_size_x * world_size_y> isometric_world;

		std::pair<float, float> world2Screen(const unsigned int& x, const unsigned int& y) const;
		sf::Vector2u screen2World(const sf::Vector2i& mouse_pos, sf::Vector2f top_left_corner) const;
		void read_tiles();
	};
}
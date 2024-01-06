#pragma once

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include "game_context.hpp"
#include "texture_manager.hpp"
#include "character.hpp"

namespace rendering
{
	constexpr unsigned int world_size_x   = 20;
	constexpr unsigned int world_size_y   = 20;
	const     std::string  filename       = "map.dat";

	enum class direction { forward, backward};
	

	class scene_manager {
	public:
		explicit scene_manager(const game_infrastructure::game_context& context);
		void     draw(sf::RenderWindow& window);
		void     edit_tile(sf::Vector2i mouse_pos, sf::Vector2f top_left_corner, direction direction);
		void     write_tiles() const;
	private:
		game_infrastructure::game_context                    context;
		std::array<unsigned int, world_size_x* world_size_y> isometric_world;
		GameObjects::character                               main_char;

		std::pair<float, float> world2Screen(const unsigned int& x, const unsigned int& y) const;
		sf::Vector2u            screen2World(const sf::Vector2i& mouse_pos, sf::Vector2f top_left_corner) const;
		void                    read_tiles();
	};
}
#pragma once

#include <SFML/Graphics.hpp>

#include "game_context.hpp"

namespace rendering
{
	constexpr int window_edge_offset = 200;  // There is a disrepancy between window size and the mouse position. This offset will be used for detecting whether mouse is at the border of screen or not
	constexpr int map_move_speed     = 1;       // how fast should we move map when mouse is in window borders

	class view_manager {
	public:
		explicit     view_manager(const game_infrastructure::game_context & context);
		sf::View     get_view() const;
		sf::Vector2f get_top_left_corner() const;
		void         update(sf::Vector2i mouse_pos);	// TODO: still not too happy with this function. in the future we might add zoom. We can overload same function name with different arguments perhaps?

	private:
		sf::View                          view;
		game_infrastructure::game_context context;
	};
}
#include "view_manager.hpp"

rendering::view_manager::view_manager(const game_infrastructure::game_context& context)
	: context(context)
{
	view.setSize(static_cast<float>(context.get_screen_resolution().x), static_cast<float>(context.get_screen_resolution().y)); // Set the size of the view to match the window size
	
	//TODO: set view center to actual world center position. possible solution: move sf:view to scene manager because SceneManager actually knows world limits. alternative move world_size_x, tile_width, etc to GameContext
	view.setCenter(0, 1440); // Set the initial center of the view
}

sf::View rendering::view_manager::get_view() const
{
	return view;
}

void rendering::view_manager::update(sf::Vector2i mouse_pos)
{
    sf::Vector2u window_size = context.get_screen_resolution();

    // todo: don't move view if we are already at the border
    // Check if mouse is at the border of the window
    if (mouse_pos.x <= window_edge_offset) {
        view.move(-map_move_speed, 0);
    }
    else if (mouse_pos.x >= window_size.x - window_edge_offset) {
        view.move(map_move_speed, 0);
    }

    if (mouse_pos.y <= window_edge_offset) {
        view.move(0, -map_move_speed);
    }
    else if (mouse_pos.y >= window_size.y - window_edge_offset) {
        view.move(0, map_move_speed);
    }
}


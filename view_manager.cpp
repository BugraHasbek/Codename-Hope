#include "view_manager.hpp"
#include <iostream>

rendering::view_manager::view_manager(const game_infrastructure::game_context& context)
	: context(context)
{
	view.setSize(static_cast<float>(context.get_screen_resolution().x), static_cast<float>(context.get_screen_resolution().y)); // Set the size of the view to match the window size
    
    // TODO: there is a weird bug here. sometimes center is not set correctly in a run but the next run it will be correct and then the next run it will be incorrect again
    // this bug is triggered only in certain circumstances. for example if the view is centered on one of the edges it works correct all the time but if view is centered in the middle of isometric map bug occurs
    std::cout << "setting center as " << context.get_view_center().x << " " << context.get_view_center().y << std::endl;
	view.setCenter(context.get_view_center()); // Set the initial center of the view as the view center of previous run
}

sf::View rendering::view_manager::get_view() const
{
	return view;
}

sf::Vector2f rendering::view_manager::get_top_left_corner() const
{
    auto retval = view.getCenter();
    retval.x -= (view.getSize().x / 2.0f);
    retval.y -= (view.getSize().y / 2.0f);
    return retval;
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


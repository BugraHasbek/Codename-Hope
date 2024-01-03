#include "game.hpp"
#include <math.h>
#include <iostream>

namespace game_infrastructure
{
    game::game()
        : window(sf::VideoMode(context.get_screen_resolution().x, context.get_screen_resolution().y), "Codename Hope", sf::Style::Close),
          scene_manager(context),
          view_manager(context)
    {
    }

	void game::run()
	{       
        window.setView(view_manager.get_view());

        sf::Event event;
        
        // Start the game loop
        while (window.isOpen())
        {
            // Process events
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();

                // Detect left mouse click
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    scene_manager.edit_tile(mouse_pos, view_manager.get_top_left_corner(), rendering::direction::forward);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    scene_manager.edit_tile(mouse_pos, view_manager.get_top_left_corner(), rendering::direction::backward);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                scene_manager.write_tiles();

                context.set_view_center(view_manager.get_view().getCenter());
                context.write_context();
                return;
            }

            // Move map if mouse is on screen borders
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            view_manager.update(mouse_pos);

            // Draw the background and character sprites
            window.clear(sf::Color(255,255,255,255));
            scene_manager.draw(window);
            window.setView(view_manager.get_view());
            window.display();
        }
	}
}

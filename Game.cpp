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
            }

            // Detect mouse movement
            if (event.type == sf::Event::MouseMoved) 
            {
                // Update the view
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                view_manager.update(mouse_pos);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return;
            }

            // Draw the background and character sprites
            window.clear(sf::Color(255,255,255,255));
            scene_manager.draw(window);
            window.setView(view_manager.get_view());
            window.display();
        }
	}

}

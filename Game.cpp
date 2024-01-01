#include "game.hpp"
#include <math.h>
#include <iostream>

namespace game_infrastructure
{
    constexpr int window_edge_offset = 50;  // There is a disrepancy between window size and the mouse position. This offset will be used for detecting whether mouse is at the border of screen or not

    game::game()
    {
        context.display.screen_height = 1440;
        context.display.screen_width = 2560;
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(static_cast<unsigned int>(context.display.screen_width), static_cast<unsigned int>(context.display.screen_height)), "Codename Hope", sf::Style::Close);
    }

	void game::run()
	{
        sf::View view;
        view.setSize(context.display.screen_width, context.display.screen_height); // Set the size of the view to match the window size

        //TODO: set view center to actual world center position. possible solution: move sf:view to scene manager because SceneManager actually knows world limits. alternative move world_size_x, tile_width, etc to GameContext
        view.setCenter(0, 1440); // Set the initial center of the view
        window->setView(view);

        sf::Event event;
        float moveSpeed = 5.0f; // Adjust this speed to your preference


        // Start the game loop
        while (window->isOpen())
        {
            // Process events
            while (window->pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window->close();
            }

            // Detect mouse movement
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                sf::Vector2u windowSize = window->getSize();

                std::cout << "X: " << mousePos.x << " Y:" << mousePos.y << std::endl;

                // todo: don't move view if we are already at the border
                // Check if mouse is at the border of the window
                if (mousePos.x <= window_edge_offset) {
                    view.move(-moveSpeed, 0);
                }
                else if (mousePos.x >= windowSize.x - window_edge_offset) {
                    view.move(moveSpeed, 0);
                }
                if (mousePos.y <= window_edge_offset) {
                    view.move(0, -moveSpeed);
                }
                else if (mousePos.y >= windowSize.y - window_edge_offset) {
                    view.move(0, moveSpeed);
                }

                // Update the view
                window->setView(view);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return;
            }

            // Draw the background and character sprites
            window->clear(sf::Color(255,255,255,255));
            scene_manager.draw(window, context);
            window->display();

        }
	}

}

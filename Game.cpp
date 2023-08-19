#include "Game.hpp"
#include "SchoolExteriorScene.hpp"
#include "DormitoryScene.hpp"
#include "UI.hpp"
#include "MainCharacter.hpp"
#include "LocationLabel.hpp"
#include "Event.hpp"
#include <math.h>

constexpr unsigned int screen_width = 2560;
constexpr unsigned int screen_height = 1440;

namespace game_infrastructure
{
    game::game()
	    :window_(std::make_shared<sf::RenderWindow>(sf::VideoMode(screen_width, screen_height), "Codename Hope", sf::Style::Close)),
         school_exterior_(std::make_unique<rendering::school_exterior_scene>()),
         dormitory_(std::make_unique<rendering::dormitory_scene>()),
         ui_(std::make_unique<rendering::UI>())
    {
        
    }

	void game::run()
	{
        // Create a clock to measure elapsed time
        sf::Clock clock;
        sf::Event event;

        // create scene objects
		auto player_character = std::make_shared<characters::main_character>();

        // attach to the scene
        dormitory_->attach_pc(player_character);

        // Start the game loop
        while (window_->isOpen())
        {
            // Measure elapsed time
            const float delta_time = clock.restart().asSeconds();

            // Process events
            
            while (window_->pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window_->close();
            }

            // Handle keyboard input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player_character->move(logic::move_direction::up, delta_time);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player_character->move(logic::move_direction::down, delta_time);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player_character->move(logic::move_direction::left, delta_time);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player_character->move(logic::move_direction::right, delta_time);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return;
            }

            // Draw the background and character sprites
            window_->clear();
            dormitory_->draw(window_);
            ui_->draw(window_);
            window_->display();

        }
	}

}

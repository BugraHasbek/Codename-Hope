#include "Game.hpp"
#include "SchoolExteriorScene.hpp"
#include "MainCharacter.hpp"

namespace game_infrastructure
{
    game::game()
	    :window_(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Codename Hope", sf::Style::Close)),
	     scene_(std::make_unique<rendering::school_exterior_scene>())
    {
        
    }

	void game::run()
	{
		std::shared_ptr<characters::main_character> player_character = std::make_shared<characters::main_character>();

        scene_->attach(player_character);

        // todo: move to character class
        // Set the character's movement speed
        float movementSpeed = 100.f;

        // Create a clock to measure elapsed time
        sf::Clock clock;

        // Start the game loop
        while (window_->isOpen())
        {
            // Measure elapsed time
            float deltaTime = clock.restart().asSeconds();

            // Process events
            sf::Event event;
            while (window_->pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window_->close();
            }

            // Handle keyboard input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player_character->move(logic::move_direction::up, deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player_character->move(logic::move_direction::down, deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player_character->move(logic::move_direction::left, deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player_character->move(logic::move_direction::right, deltaTime);
            }

            // Draw the background and character sprites
            scene_->draw(window_);
        }
	}

}

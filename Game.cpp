#include "Game.hpp"
#include "SchoolExteriorScene.hpp"
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
	     scene_(std::make_unique<rendering::school_exterior_scene>())
    {
        
    }

	void game::run()
	{
        // Create a clock to measure elapsed time
        sf::Clock clock;
        sf::Event event;

        // create scene objects
		auto player_character = std::make_shared<characters::main_character>();


        // mall label
        auto mall_label = std::make_shared<rendering::location_label>("Mall", std::pair<float, float>(200.f, 300.f));
    	auto show_mall_guard_function = [](std::pair<float, float> player_position) { return abs(player_position.first - 200.f) + abs(player_position.second - 300.f) < 40; };
        auto show_mall_action_function = [mall_label]() {mall_label->show(); };
        const game_infrastructure::event show_mall_label_event(show_mall_guard_function, show_mall_action_function);
        auto hide_mall_guard_function = [](std::pair<float, float> player_position) { return abs(player_position.first - 200.f) + abs(player_position.second - 300.f) >= 40; };
        auto hide_mall_action_function = [mall_label]() {mall_label->hide(); };
        const game_infrastructure::event hide_mall_label_event(hide_mall_guard_function, hide_mall_action_function);
        mall_label->add_event(show_mall_label_event);
        mall_label->add_event(hide_mall_label_event);
        //mall_label->hide();

        // school label
        auto school_label = std::make_shared<rendering::location_label>("School", std::pair<float, float>(500.f, 300.f));
        auto show_school_guard_function = [](std::pair<float, float> player_position) { return abs(player_position.first - 500.f) + abs(player_position.second - 300.f) < 40; };
        auto show_school_action_function = [school_label]() {school_label->show(); };
        const game_infrastructure::event show_school_label_event(show_school_guard_function, show_school_action_function);
        auto hide_school_guard_function = [](std::pair<float, float> player_position) { return abs(player_position.first - 500.f) + abs(player_position.second - 300.f) >= 40; };
        auto hide_school_action_function = [school_label]() {school_label->hide(); };
        const game_infrastructure::event hide_school_label_event(hide_school_guard_function, hide_school_action_function);
        school_label->add_event(show_school_label_event);
        school_label->add_event(hide_school_label_event);
        //school_label->hide();

        // attach to the scene
        scene_->attach_pc(player_character);
        scene_->attach(school_label);
        scene_->attach(mall_label);

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
            scene_->draw(window_);
        }
	}

}

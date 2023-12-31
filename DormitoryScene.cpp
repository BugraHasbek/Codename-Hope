#include "DormitoryScene.hpp"

namespace rendering
{
	// TODO: we will use sf:View for supporting multiple resolutions so for now we will with scale hardcoded width height
	constexpr unsigned int screen_width = 2560;
	constexpr unsigned int screen_height = 1440;

	dormitory_scene::dormitory_scene()
		:dorm_001_(sf::Sprite())
	{
		// Load the background texture
		if (!dorm_001_texture_.loadFromFile("Media/Textures/scenes/Room_Umut_2560x1440.jpg"))
		{
			throw std::exception("umut's dorm room texture cannot be loaded");
		}

		// Set the scale factor to expand the texture to the screen size
		sf::Vector2f scale_factor(
			static_cast<float>(screen_width) / dorm_001_texture_.getSize().x,
			static_cast<float>(screen_height) / dorm_001_texture_.getSize().y
		);

		// Set the scale of the sprite
		dorm_001_.setScale(scale_factor);
		dorm_001_.setTexture(dorm_001_texture_);

		// TODO: YAPILACAKLAR
		// 1. create a view and move it around the sprite
		/*
		sf::View view;
		view.setSize(window.getSize().x, window.getSize().y); // Set the size of the view to match the window size
		view.setCenter(player.getPosition()); // Set the initial center of the view to the player's position
		window.setView(view); // Apply the view to the window

		// Update the view's center to follow the player (call this in your game loop)
		view.setCenter(player.getPosition());
		window.setView(view);
		*/
	}

	void dormitory_scene::draw(std::shared_ptr<sf::RenderWindow>& window)	
	{
		// Draw the background and character sprites
		window->draw(dorm_001_);

		for (auto iterator = drawable_objects_.begin(); iterator != drawable_objects_.end(); ++iterator)
		{
			iterator->second->process_events(main_character_->get_location());

			if (iterator->second->is_visible())
			{
				window->draw(*iterator->second->get_sprite());
			}
		}

		window->draw(*main_character_->get_sprite());

		
	}
}

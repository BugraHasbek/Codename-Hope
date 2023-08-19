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
		if (!dorm_001_texture_.loadFromFile("Media/Textures/scenes/dormitory-001.png"))
		{
			throw std::exception("dorm room texture cannot be loaded");
		}

		// Set the scale factor to expand the texture to the screen size
		sf::Vector2f scale_factor(
			static_cast<float>(screen_width) / dorm_001_texture_.getSize().x,
			static_cast<float>(screen_height) / dorm_001_texture_.getSize().y
		);

		// Set the scale of the sprite
		dorm_001_.setScale(scale_factor);
		dorm_001_.setTexture(dorm_001_texture_);
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

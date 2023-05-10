#include "SchoolExteriorScene.hpp"

namespace rendering
{
	school_exterior_scene::school_exterior_scene()
	{
		// Load the background texture
		if (!background_texture_.loadFromFile("Media/Textures/school_exterior_background.jpg"))
		{
			throw std::exception("school exterior background texture cannot be loaded");
		}
		background_ = sf::Sprite(background_texture_);
	}

	void school_exterior_scene::draw(std::shared_ptr<sf::RenderWindow>& window)
	{
		// Draw the background and character sprites
		window->clear();
		window->draw(background_);

		for(auto iterator = drawable_objects_.begin(); iterator != drawable_objects_.end(); ++iterator)
		{
			iterator->second->process_events(main_character_->get_location());

			if (iterator->second->is_visible())
			{
				window->draw(*iterator->second->get_sprite());
			}
		}

		window->draw(*main_character_->get_sprite());
		
		window->display();
	}
}

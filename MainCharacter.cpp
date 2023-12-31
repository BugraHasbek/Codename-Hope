#include "MainCharacter.hpp"
#include <iostream>

namespace characters
{
	main_character::main_character()
	{
		// Load the main character texture
		if (!character_texture_.loadFromFile("Media/Textures/characters/Sprite-0001.png")) {
			throw std::exception("main character texture cannot be loaded");
		}

		// Create the main character sprite
		sprite_ = std::make_shared<sf::Sprite>(character_texture_);

		// Set the character's starting position
		x_ = 400;
		y_ = 300;
		sprite_->setPosition(x_, y_);

		movement_speed_ = 200.f;

		// Set the character's initial size
		sprite_->setScale(3, 3);

		drawable_object_id_ = "player";
	}

	// TODO: move this function to scene class.
	// maincharacter class cannot know if there is an obstacle or not.
	// each scene should contain boundaries and obstacles and main char should not run into walls
	void main_character::move(const logic::move_direction direction, const float delta_time)
	{
		if (direction == logic::move_direction::up)
		{
			y_ -= movement_speed_ * delta_time;
		}
		if (direction == logic::move_direction::down)
		{
			y_ += movement_speed_ * delta_time;
		}
		if (direction == logic::move_direction::left)
		{
			x_ -= movement_speed_ * delta_time;
		}
		if (direction == logic::move_direction::right)
		{
			x_ += movement_speed_ * delta_time;
		}

		sprite_->setPosition(x_, y_);
	}

	std::pair<float, float> main_character::get_location() const
	{
		return std::pair<float, float>(x_, y_);
	}
}

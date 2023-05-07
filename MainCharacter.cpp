#include "MainCharacter.hpp"
#include <iostream>

namespace characters
{
	main_character::main_character()
	{
		// Load the main character texture
		if (!character_texture_.loadFromFile("Media/Textures/character.png")) {
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
		sprite_->setScale(0.25, 0.25); // double the size of the character sprite

		drawable_object_id_ = "player";
	}

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
}

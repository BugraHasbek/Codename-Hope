#pragma once

#include "IDrawable.hpp"
#include "IMovable.hpp"

namespace characters
{
	class main_character final : public rendering::IDrawable,
		                         public logic::IMovable
	{
	public:
		main_character();
		sf::Sprite get_sprite() override;
		void move(logic::move_direction direction, float delta_time) override;

	private:
		sf::Texture character_texture_;
	};

}

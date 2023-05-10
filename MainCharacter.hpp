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
		void move(logic::move_direction direction, float delta_time) override;
		std::pair<float, float> get_location() const;

	private:
		sf::Texture character_texture_;
	};

}

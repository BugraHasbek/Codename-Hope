#pragma once

#include <SFML/Graphics.hpp>


namespace rendering
{
	class IDrawable
	{
	public:
		virtual sf::Sprite get_sprite() = 0;
		std::string get_id();

	protected:
		std::string drawable_object_id_;
		sf::Sprite sprite_;
	};

	inline std::string IDrawable::get_id()
	{
		return drawable_object_id_;
	}
}


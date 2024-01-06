#pragma once
#include <SFML/Graphics.hpp>

namespace GameObjects
{
	enum class status {idle};

	class character
	{
	public:
		character();
		void draw(sf::RenderWindow& window);
	
	private:
		sf::Vector2f location = { 400.0f, 600.0f };
		status current_status = status::idle;
		unsigned int animation_index = 0;
		std::vector<sf::Sprite> idle_animations;
	};


}
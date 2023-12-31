#include "UI.hpp"

namespace rendering
{
	UI::UI()
	{
		// Load the background texture
		if (!date_texture_.loadFromFile("Media/Textures/date/9_4_2023_1.png"))
		{
			throw std::exception("date texture cannot be loaded");
		}
		date_ = sf::Sprite(date_texture_);
	}

	void UI::draw(std::shared_ptr<sf::RenderWindow>& window)
	{
		// Draw the background and character sprites
		window->draw(date_);
	}
}

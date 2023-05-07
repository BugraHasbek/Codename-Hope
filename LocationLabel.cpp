#include "LocationLabel.hpp"

namespace rendering
{
	location_label::location_label(const std::string& text, std::pair<float,float> location)
	{
		// Load a font
		if (!font_.loadFromFile("Media/fonts/arial/arial.ttf"))
		{
			throw std::exception("font cannot be loaded");
		}

		text_ = sf::Text(text, font_, 18); // Create a text object
		text_.setFillColor(sf::Color::Black); // Set the text color

		// get the local bounds of the text
		sf::FloatRect bounds = text_.getGlobalBounds();
		constexpr float padding = 5.f;
		texture_.create(text_.getGlobalBounds().left + text_.getGlobalBounds().width + padding,
			            text_.getGlobalBounds().top + text_.getGlobalBounds().height + padding);

		texture_.clear(sf::Color::White); // Clear the texture with a background color

		texture_.draw(text_); // Draw the text on the texture

		texture_.display(); // Update the texture

		drawable_object_id_ = text;//TODO: if two labels with same text attached to same scene, only one of them will be displayed

		sprite_ = std::make_shared<sf::Sprite>(texture_.getTexture()); // Create a sprite with the texture

		sprite_->setPosition(location.first, location.second);

		visibility_ = true;
	}
}


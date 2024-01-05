#include "character.hpp"
#include "texture_manager.hpp"
#include <iostream>

GameObjects::character::character()
{
	// create and store sprites 
	std::vector<sf::Texture>& char_textures(rendering::texture_manager::getInstance()->get_char_texture_pack());
	for (size_t index = 0; index < char_textures.size(); index++)
	{
		sf::Sprite sprite(char_textures.at(index));
		idle_animations.push_back(sprite);
	}
}

void GameObjects::character::draw(sf::RenderWindow& window)
{
	if(current_status == status::idle)
	{
		sf::Sprite sprite = idle_animations.at(animation_index / 150);
		sprite.setPosition(location);
		window.draw(sprite);
		animation_index = (animation_index + 1) % (idle_animations.size() * 150);
	}
}

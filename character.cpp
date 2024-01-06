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
    // TODO: Handle keyboard input
    // I was planning to handle keyboard events in game.cpp but perhaps it is overengineering. I think each ondividual game object can handle events individually
    // TODO: calculate delta time.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        location.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        location.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        location.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        location.x += 1;
    }

	if(current_status == status::idle)
	{
		sf::Sprite sprite = idle_animations.at(animation_index / 150);
		sprite.setPosition(location);   // TODO: we need a transformation here.. chracter class should know position in term of game world coordinates. actual isometric coordinates should be used only before drawing sprite
		window.draw(sprite);
		animation_index = (animation_index + 1) % (idle_animations.size() * 150);
	}
}

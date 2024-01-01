#include "scene_manager.hpp"
#include <cmath>
#include <iostream>

constexpr unsigned int tile_width  = 256;
constexpr unsigned int tile_height = 128;

rendering::scene_manager::scene_manager(const game_infrastructure::game_context& context)
	: context(context),
	isometric_world{0}
{
	if (!invalid_texture.loadFromFile("Media/Textures/tileset/invalid.png"))
	{
		throw std::exception("invalid tile texture cannot be loaded");
	}

	if (!empty_texture.loadFromFile("Media/Textures/tileset/empty.png"))
	{
		throw std::exception("empty tile texture cannot be loaded");
	}

	if (!green_texture.loadFromFile("Media/Textures/tileset/green.png"))
	{
		throw std::exception("green tile texture cannot be loaded");
	}

	isometric_world.at(0) = 1;
	isometric_world.at(1) = 1;
	isometric_world.at(2) = 1;
	isometric_world.at(3) = 1;
	isometric_world.at(4) = 1;
	isometric_world.at(world_size_x) = 1;
	isometric_world.at(world_size_x * 2) = 1;
	isometric_world.at(world_size_x * 3) = 1;
	isometric_world.at(world_size_x * 4) = 1;
	isometric_world.at(world_size_x * 5) = 1;
	isometric_world.at(world_size_x * 6) = 1;
	isometric_world.at(world_size_x * 7) = 1;
	isometric_world.at(world_size_x * 8) = 1;
	isometric_world.at(world_size_x * 9) = 1;
}

void rendering::scene_manager::draw(sf::RenderWindow& window)
{
	sf::Sprite tile;
	for (std::size_t x_index = 0; x_index < world_size_x; x_index++)
	{
		for (std::size_t y_index = 0; y_index < world_size_y; y_index++)
		{
			switch (isometric_world[x_index + y_index * world_size_x])
			{
			case 0:
				tile.setTexture(empty_texture);
				break;
			case 1:
				tile.setTexture(green_texture);
				break;
			default:
				tile.setTexture(invalid_texture);
				std::cout << "ERROR: isometric map[" << x_index << "][" << y_index << "] : " << isometric_world[x_index + y_index * world_size_x] << std::endl;
				break;
			}
			std::pair<float, float> screen_location = world2Screen(x_index, y_index);
			tile.setPosition(screen_location.first, screen_location.second);
			window.draw(tile);
		}
	}
}

std::pair<float, float> rendering::scene_manager::world2Screen(const unsigned int& x, const unsigned int& y) const
{
	float screen_x = static_cast<float>(x * tile_width) / 2.0f - static_cast<float>(y * tile_width) / 2.0f;
	float screen_y = static_cast<float>(y * tile_height) / 2.0f + static_cast<float>(x * tile_height) / 2.0f;
	return std::pair<float, float>(screen_x, screen_y);
}

#include "scene_manager.hpp"
#include <cmath>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

constexpr float tile_width  = 256.0f;
constexpr float tile_height = 128.0f;

rendering::scene_manager::scene_manager(const game_infrastructure::game_context& context)
	: context(context),
	  isometric_world{ 0 }
{
	read_tiles();
}

void rendering::scene_manager::draw(sf::RenderWindow& window)
{
	for (std::size_t x_index = 0; x_index < world_size_x; x_index++)
	{
		for (std::size_t y_index = 0; y_index < world_size_y; y_index++)
		{
			sf::Sprite tile;
			tile.setTexture(texture_manager.get_texture(isometric_world[x_index + y_index * world_size_x]));
			std::pair<float, float> screen_location = world2Screen(x_index, y_index);
			tile.setPosition(screen_location.first, screen_location.second);
			window.draw(tile);
		}
	}
}

void rendering::scene_manager::edit_tile(sf::Vector2i mouse_pos, sf::Vector2f top_left_corner, direction direction)
{
	sf::Vector2u world_index = screen2World(mouse_pos, top_left_corner);
	auto isometric_index = world_index.x + world_index.y * world_size_x;

	if (isometric_index < isometric_world.size())
	{
		isometric_world.at(isometric_index) = direction == direction::forward ? texture_manager.get_next_texture_id(isometric_world.at(isometric_index)) :
			                                                                    texture_manager.get_prev_texture_id(isometric_world.at(isometric_index));
	}
}

void rendering::scene_manager::write_tiles() const
{
	std::stringstream content;
	std::ofstream file(filename, std::ios::out);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}
	content << world_size_x << " " << world_size_y << std::endl;

	for (std::size_t x_index = 0; x_index < world_size_x; x_index++)
	{
		for (std::size_t y_index = 0; y_index < world_size_y; y_index++)
		{
			content << isometric_world.at(x_index + y_index * world_size_x) << " ";
		}
		content << std::endl;
	}
	file.write(content.str().c_str(), content.str().length());
	file.close();
}

void rendering::scene_manager::read_tiles()
{
	std::ifstream file(filename, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}

	unsigned int width;
	unsigned int height;
	file >> width >> height;

	if (width != world_size_x || height != world_size_y) {
		std::cerr << "Map dimensions do not match world size.\n";
		return;
	}

	for (unsigned int x_index = 0; x_index < world_size_x; ++x_index) {
		for (unsigned int y_index = 0; y_index < world_size_y; ++y_index) {
			file >> isometric_world[x_index + y_index * world_size_x];
		}
	}

	file.close();
}

std::pair<float, float> rendering::scene_manager::world2Screen(const unsigned int& x, const unsigned int& y) const
{
	auto x_ = static_cast<float>(x);
	auto y_ = static_cast<float>(y);

	//simplification of  (x * tile_width) / 2 - (y * tile_width) / 2;
	float screen_x = (x_ - y_) * tile_width / 2.0f;

	//simplification of  (x * tile_width) / 2 + (y * tile_width) / 2;
	float screen_y = (x_ + y_) * tile_height / 2.0f;

	return std::pair<float, float>(screen_x, screen_y);
}

sf::Vector2u rendering::scene_manager::screen2World(const sf::Vector2i& mouse_pos, sf::Vector2f top_left_corner) const
{
	auto x_ = static_cast<float>(mouse_pos.x) + top_left_corner.x;
	auto y_ = static_cast<float>(mouse_pos.y) + top_left_corner.y;

	auto row = (x_ / 128.0f) - 1.0f;
	auto column = (y_ / 64.0f);

	auto isometric_x = static_cast<unsigned int>((column + row) / 2.0f);
	auto isometric_y = static_cast<unsigned int>((column - row) / 2.0f);

	return sf::Vector2u(isometric_x, isometric_y);
}



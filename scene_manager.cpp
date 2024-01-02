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

	read_tiles();

	rectangle.setFillColor(sf::Color(0, 0, 0, 0));
	rectangle.setOutlineColor(sf::Color(255, 0, 0, 255));
	rectangle.setOutlineThickness(1);
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

	window.draw(rectangle);
}

void rendering::scene_manager::edit_tile(sf::Vector2i mouse_pos, sf::Vector2f top_left_corner)
{
	sf::Vector2u world_index = screen2World(mouse_pos, top_left_corner);
	auto isometric_index = world_index.x + world_index.y * world_size_x;

	if (isometric_index < isometric_world.size())
	{
		isometric_world.at(isometric_index) = (isometric_world.at(isometric_index)  + 1) % tileset_count;
	}
}

void rendering::scene_manager::write_tiles() const
{
	std::ofstream map("map.dat", std::ios::out);
	std::stringstream content;
	content << world_size_x << " " << world_size_y << std::endl;

	for (std::size_t x_index = 0; x_index < world_size_x; x_index++)
	{
		for (std::size_t y_index = 0; y_index < world_size_y; y_index++)
		{
			content << isometric_world.at(x_index + y_index * world_size_x) << " ";
		}
		content << std::endl;
	}
	map.write(content.str().c_str(), content.str().length());
	map.close();
}

void rendering::scene_manager::read_tiles()
{
	std::ifstream file("map.dat", std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Error opening file map.dat" << std::endl;
		return;
	}

	unsigned int width;
	unsigned int height;
	file >> width >> height;

	if (width != world_size_x || height != world_size_y) {
		std::cerr << "Map dimensions do not match world size.\n";
		return;
	}

	for (unsigned int i = 0; i < width; ++i) {
		for (unsigned int j = 0; j < height; ++j) {
			file >> isometric_world[i * world_size_y + j];
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
	
	std::cout << "mouse pos:[" << mouse_pos.x << " , " << mouse_pos.y  << "]" << std::endl;
	std::cout << "view port:[" << top_left_corner.x << " , " << top_left_corner.y << "]" << std::endl;
	std::cout << "[x_, y_] :[" << x_ << ", " << y_ << std::endl;

	auto row = (x_ / 128.0f) - 1.0f;
	auto column = (y_ / 64.0f);
	std::cout << "row: " << row << std::endl;
	std::cout << "column: " << column << std::endl;

	auto isometric_x = static_cast<unsigned int>((column + row) / 2.0f);
	auto isometric_y = static_cast<unsigned int>((column - row) / 2.0f);
	std::cout << "isometric_x: " << isometric_x << std::endl;
	std::cout << "isometric_y: " << isometric_y << std::endl;

	return sf::Vector2u(isometric_x, isometric_y);
}



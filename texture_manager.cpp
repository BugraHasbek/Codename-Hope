#include "texture_manager.hpp"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

rendering::texture_manager::texture_manager()
{
	read_all_textures();
}

sf::Texture& rendering::texture_manager::get_texture(const unsigned int texture_index)
{
	return textures.at(texture_index);
}

unsigned int rendering::texture_manager::get_next_texture_id(const unsigned int texture_index) const
{
	return (texture_index + 1) % textures.size();
}

unsigned int rendering::texture_manager::get_prev_texture_id(const unsigned int texture_index) const
{
	return (texture_index + textures.size() - 1) % textures.size();
}

void rendering::texture_manager::read_all_textures()
{
	read_texture_packs(large_tile_directory_path, large_tile_width, large_tile_height);
}

void rendering::texture_manager::read_texture_packs(const std::string& directory_path, const unsigned int& tile_width, const unsigned int& tile_height)
{
	std::vector<std::string> png_files;
	// Check if the directory exists
	if (fs::exists(directory_path) && fs::is_directory(directory_path))
	{
		// Iterate through the directory and find PNG files
		for (const auto& entry : fs::directory_iterator(directory_path))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".png")
			{
				png_files.push_back(directory_path + entry.path().filename().string());
				std::cout << "Found texture: " << directory_path + entry.path().filename().string() << "\n";
			}
		}
	}
	else
	{
		std::cerr << "Directory does not exist or is invalid.\n";
	}

	// Sort the vector alphabetically
	std::sort(png_files.begin(), png_files.end());

	for (const auto& texture_name : png_files)
	{
		sf::Image image;
		if (!image.loadFromFile(texture_name))
		{
			// Error handling if the file fails to load
			std::cerr << "Failed to load the image." << std::endl;
			continue;
		}

		// Get the dimensions of the image
		unsigned int image_width = image.getSize().x;
		unsigned int image_height = image.getSize().y;

		for (int x_index = 0; x_index < image_width / tile_width; x_index++)
		{
			for (int y_index = 0; y_index < image_height / tile_height; y_index++)
			{
				sf::Texture texture;
				sf::IntRect dimension{ static_cast<int>(x_index * tile_width), static_cast<int>(y_index * tile_height) , static_cast<int>(tile_width), static_cast<int>(tile_height) };	// left, top, width, height
				if (!texture.loadFromFile(texture_name, dimension))
				{
					std::cerr << "texture cannot be loaded: " + texture_name << ".\n";
				}
				textures.push_back(texture);
			}
		}
		std::cout << "texture size after reading " << texture_name << " is " << textures.size() << "\n";
	}
}

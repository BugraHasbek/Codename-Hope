#pragma once

#include <SFML/Graphics.hpp>


namespace rendering
{
	const     std::string  large_tile_directory_path = "Media/Textures/tileset/256x128/";
	constexpr unsigned int large_tile_width          = 256;
	constexpr unsigned int large_tile_height         = 128;

	class texture_manager
	{
	public:
		texture_manager();
		sf::Texture&  get_texture(const unsigned int texture_index);
		unsigned int get_next_texture_id(const unsigned int texture_index) const;
		unsigned int get_prev_texture_id(const unsigned int texture_index) const;

	private:
		std::vector<sf::Texture> textures;

		void read_all_textures();
		void read_texture_packs(const std::string & directory_path, const unsigned int & tile_width, const unsigned int & tile_height);
	};
}
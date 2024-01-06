#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace rendering
{
	const     std::string  char_tile_directory_path  = "Media/Textures/character/256x256/";
	constexpr unsigned int char_tile_width = 256;
	constexpr unsigned int char_tile_height = 256;
	const     std::string  large_tile_directory_path = "Media/Textures/tileset/256x128/";	// TODO: perhaps I should rename it to what it does instead of its size, for example world tiles or forest tiles, etc...
	constexpr unsigned int large_tile_width          = 256;	
	constexpr unsigned int large_tile_height         = 128;

	class texture_manager
	{
	public:
		static std::shared_ptr<texture_manager> getInstance();
		sf::Texture& get_texture(const unsigned int texture_index);
		sf::Texture& get_char_texture(const unsigned int texture_index);
		std::vector<sf::Texture>&  get_char_texture_pack();
		unsigned int get_next_texture_id(const unsigned int texture_index) const;
		unsigned int get_prev_texture_id(const unsigned int texture_index) const;

	private:
		static std::shared_ptr<texture_manager> instance;
		std::vector<sf::Texture> textures;
		std::vector<sf::Texture> char_textures;

		void read_all_textures();
		void read_texture_packs(const std::string & directory_path, const unsigned int & tile_width, const unsigned int & tile_height, std::vector<sf::Texture>& texture_vector);
	};
}
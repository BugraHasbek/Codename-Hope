#include "game_context.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

game_infrastructure::game_context::game_context()
{
	// default values in case context.dat is deleted
	settings.screen_resolution.x = 2560;
	settings.screen_resolution.y = 1440;
	read_context();
}

void game_infrastructure::game_context::write_context() const
{
	std::stringstream content;
	std::ofstream file(filename, std::ios::out);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}
	content << settings.screen_resolution.x << " " << settings.screen_resolution.y << std::endl;
	content << settings.view_center.x       << " " << settings.view_center.y       << std::endl;

	file.write(content.str().c_str(), content.str().length());
	file.close();
}

void game_infrastructure::game_context::read_context()
{
	std::ifstream file(filename, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}

	file >> settings.screen_resolution.x >> settings.screen_resolution.y;
	file >> settings.view_center.x >> settings.view_center.y;

	std::cout << "read center as " << settings.view_center.x << " " << settings.view_center.y << std::endl;

	file.close();
}

#pragma once

#include <SFML/Graphics.hpp>
#include "IScene.hpp"

namespace game_infrastructure
{
	class game
	{
	public:
		game();
		void run();
		
	private:
		std::shared_ptr<sf::RenderWindow>  window_;
		std::unique_ptr<rendering::IScene> school_exterior_;
		std::unique_ptr<rendering::IScene> dormitory_;
		std::unique_ptr<rendering::IScene> ui_;
	};
}

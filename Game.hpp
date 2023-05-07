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
		std::unique_ptr<rendering::IScene> scene_;
	};
}

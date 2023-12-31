#pragma once

#include <SFML/Graphics.hpp>
#include "IScene.hpp"

namespace rendering
{
	class dormitory_scene final : public IScene
	{
	public:
		dormitory_scene();
		void draw(std::shared_ptr<sf::RenderWindow>& window) override;

	private:
		sf::Texture dorm_001_texture_;
		sf::Sprite dorm_001_;
	};
}
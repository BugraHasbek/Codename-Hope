#pragma once

#include <SFML/Graphics.hpp>
#include "IScene.hpp"

namespace rendering
{
	class school_exterior_scene final : public IScene
	{
	public:
		school_exterior_scene();
		void draw(std::shared_ptr<sf::RenderWindow>& window) override;

	private:
		sf::Texture background_texture_;
		sf::Sprite background_;
	};
}
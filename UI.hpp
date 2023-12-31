#pragma once

#include <SFML/Graphics.hpp>
#include "IScene.hpp"

namespace rendering
{
	class UI final : public IScene
	{
	public:
		UI();
		void draw(std::shared_ptr<sf::RenderWindow>& window) override;

	private:
		sf::Texture date_texture_;
		sf::Sprite date_;
	};
}
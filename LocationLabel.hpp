#pragma once
#include <string>
#include "IDrawable.hpp"

namespace rendering
{
	class location_label : public IDrawable
	{
	public:
		explicit location_label(const std::string& text, std::pair<float, float> location);

	private:
		sf::Font font_;
		sf::Text text_;
		sf::RenderTexture texture_;

	};
}

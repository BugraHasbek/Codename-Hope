#pragma once

#include <SFML/Graphics.hpp>


namespace rendering
{
	class IDrawable
	{
	public:
		virtual ~IDrawable() = default;
		std::shared_ptr<sf::Sprite> get_sprite();
		std::string get_id();
		void show();
		void hide();
		bool is_visible() const;
	protected:
		std::string drawable_object_id_;
		std::shared_ptr<sf::Sprite> sprite_;
		bool visibility_ = true;
	};

	inline std::shared_ptr<sf::Sprite> IDrawable::get_sprite()
	{
		return sprite_;
	}

	inline std::string IDrawable::get_id()
	{
		return drawable_object_id_;
	}

	inline void IDrawable::show()
	{
		visibility_ = true;
	}

	inline void IDrawable::hide()
	{
		visibility_ = false;
	}

	inline bool IDrawable::is_visible() const
	{
		return visibility_;
	}
}


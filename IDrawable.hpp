#pragma once

#include <SFML/Graphics.hpp>
#include "Event.hpp"

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
		void add_event(const game_infrastructure::event& new_event);
		void process_events(std::pair<float, float> player_location) const;
	protected:
		std::string drawable_object_id_;
		std::shared_ptr<sf::Sprite> sprite_;
		bool visibility_ = true;
		std::vector<game_infrastructure::event> events_;
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

	inline void IDrawable::add_event(const game_infrastructure::event& new_event)
	{
		events_.push_back(new_event);
	}

	inline void IDrawable::process_events(std::pair<float,float> player_location) const
	{
		for (int index = 0; index < events_.size(); index++)
		{
			if(events_.at(index).check_event(player_location))
			{
				events_.at(index).execute();
			}
		}
	}
}


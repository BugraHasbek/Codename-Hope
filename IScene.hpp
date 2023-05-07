#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>
#include "IDrawable.hpp"

namespace rendering
{
	class IScene
	{
	public:
		virtual ~IScene() = default;
		virtual void draw(std::shared_ptr<sf::RenderWindow>& window) = 0;
		virtual void attach(std::shared_ptr <IDrawable> drawable_object);
		virtual void detach(const std::string& drawable_object_id);

	protected:
		std::unordered_map<std::string, std::shared_ptr<IDrawable> > drawable_objects_;
	};

	inline void IScene::attach(std::shared_ptr<IDrawable> drawable_object)
	{
		drawable_objects_.insert_or_assign(drawable_object->get_id(), drawable_object);
	}

	inline void IScene::detach(const std::string& drawable_object_id)
	{
		drawable_objects_.erase(drawable_object_id);
	}
}

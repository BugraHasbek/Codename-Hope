#pragma once
#include <utility>

namespace logic
{
	enum class move_direction
	{
		up,
		right,
		down,
		left
	};

	class IMovable
	{
	public:
		virtual ~IMovable() = default;
		virtual void move(move_direction direction, float delta_time) = 0;
		void set_speed(float speed);

	protected:
		float x_;
		float y_;
		float movement_speed_;
	};

	inline void IMovable::set_speed(float speed)
	{
		movement_speed_ = speed;
	}
}

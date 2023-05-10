#pragma once
#include <functional>

namespace game_infrastructure
{
	class event
	{
	public:
		explicit event(const std::function<bool(std::pair<float,float>)>& guard_function, const std::function<void()>& action_function);
		bool check_event(std::pair<float, float> player_position) const;
		void execute() const;

	private:
		std::function<bool(std::pair<float, float>)> guard_function_;
		std::function<void()> action_function_;
	};
	
	inline event::event(const std::function<bool(std::pair<float, float>)>& guard_function,
	                    const std::function<void()>& action_function)
	{
		guard_function_ = guard_function;
		action_function_ = action_function;
	}

	inline bool event::check_event(const std::pair<float, float> player_position) const
	{
		return guard_function_(player_position);
	}

	inline void event::execute() const
	{
		action_function_();
	}
}

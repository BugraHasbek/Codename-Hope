#pragma once

namespace game_infrastructure
{
	using display_settings = struct  {
		float screen_width;
		float screen_height;
	};

	using game_context = struct {
		display_settings display;
	};
}

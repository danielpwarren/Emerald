#pragma once

#include "core/Base.h"
#include "input/KeyCodes.h"
#include "input/MouseCodes.h"

namespace Emerald {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}

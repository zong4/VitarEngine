#pragma once

#include "Vitar/Core/KeyCodes.h"
#include "Vitar/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Vitar 
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}

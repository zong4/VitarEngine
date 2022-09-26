#pragma once

#include "Vitar/Core/Base.h"
#include "Vitar/Core/KeyCodes.h"
#include "Vitar/Core/MouseCodes.h"

namespace Vitar 
{
	class VITAR_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
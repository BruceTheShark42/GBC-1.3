#pragma once

#include <utility>
#include "Core/Keycodes.h"
#include "Core/Mousecodes.h"

class Input
{
public:
	static bool IsKeyPressed(Keycode keycode);
	static bool IsKeyReleased(Keycode keycode);

	static bool IsMouseButtonPressed(Mousecode button);
	static bool IsMouseButtonReleased(Mousecode button);

	static std::pair<float, float> GetMousePos();
	static float GetMousePosX();
	static float GetMousePosY();
};
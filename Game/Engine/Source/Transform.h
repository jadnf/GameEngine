#pragma once
#include "Vector2.h"

struct Transform {
	Vector2 position;
	float rotation;
	float scale;

	Transform() = default;
	Transform(Vector2 position, float rotation, float scale) :
		position{ position },
		rotation{ rotation },
		scale{ scale }
	{}
};
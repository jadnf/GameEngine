#include "GameData.h"

namespace GameData {
	const std::vector<Vector2> shipPoints{
		{ 0.0F,1.5f },
		{ 1.0F,0.5f },
		{ 1.5F,0.5f },
		{ 1.5F,0.5f },
		{ 2.5F,0.0f },
		{ 1.5F,-0.5f },
		{ 1.0F,-0.5f },
		{ 0.0F,-1.5f },
		{ 0.5F,0.0f },
		{ 0.0F,1.5f },
	};
	const std::vector<Vector2> bulletPoints{
		{ 5, 0 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 0 },
	};
}
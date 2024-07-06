#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle{
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float lifespan = 0;

	Particle() = default;

	Particle(Vector2 position, Vector2 velocity) : position{ position }, velocity{ velocity } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan) : position{ position }, velocity{ velocity }, lifespan{ lifespan } {}
	
	void Update(float dt);
	void Draw(Renderer& renderer);
};

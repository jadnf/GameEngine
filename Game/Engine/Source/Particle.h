#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle{
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float lifespan = 0;
	int r = 255;
	int g = 255;
	int b = 255;
	int a = 0;

	Particle() = default;

	Particle(Vector2 position, Vector2 velocity) : position{ position }, velocity{ velocity } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan) : position{ position }, velocity{ velocity }, lifespan{ lifespan } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan, int r, int g, int b, int a) : position{ position }, velocity{ velocity }, lifespan{ lifespan }, r{ r }, g{ g }, b{ b }, a{ a } {}
	
	void Update(float dt);
	void Draw(Renderer& renderer);
};

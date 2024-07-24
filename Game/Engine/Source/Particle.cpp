#include "Particle.h"

void Particle::Initialize(const Data& data)
{
	isActive = true;
	position = data.position;
	velocity = data.velocity;
	r = data.r;
	g = data.g;
	b = data.b;
	a = data.a;
}

void Particle::Update(float dt)
{
	
	if (lifespan != 0) {
		lifespan -= dt;
	}
	isActive = (lifespan <= 0);
	position = position + (velocity * dt);
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan > 0) {
		renderer.SetColor(r, g, b, a);
		renderer.DrawPoint(position.x, position.y);
		renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
	}
}

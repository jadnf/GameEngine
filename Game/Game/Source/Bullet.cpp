#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	Particle::Data data{
		m_transform.position,
		Vector2{1,0}.Rotate(random(Math::TwoPi)) * 50,
		randomf(1.3, 1.9),
		255,255,255,0
	};
	g_engine.GetPS().AddParticle(data);
	m_velocity = Vector2{ 1,0 }.Rotate(m_transform.rotation) * m_speed;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
}

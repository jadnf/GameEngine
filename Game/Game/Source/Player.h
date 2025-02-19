#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{speed}
	{}


	void Update(float dt);
	virtual void OnCollision(Actor* actor);


private:
	float m_speed = 0.0f;
	float m_fireTimer = 2.0f;
};
#pragma once

#include "game_object.h"
#include "Box2D\Box2D.h"

class Particle : public GameObject {

public:

	b2Body* m_body;
	float life;
	float life_time;

	void Init(float life);
};
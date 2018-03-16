#pragma once

#include "Box2D\Box2D.h"
#include "game_object.h"

/* Class for a single particle. Is a game object to be able to be put in a ObjectPool */
class Particle : public GameObject {

public:

	b2Body* m_body;		// Same body for every particle
	float life;			// The total time that the particle exists
	float life_time;	// The amount of time the particle has been active

	virtual void Init(float life);
};
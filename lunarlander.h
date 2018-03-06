#pragma once

#include "game.h"
#include "Box2D/Box2D.h"
#include "collision_callback.h"

#include "physics_component.h"
#include "particle_component.h"

#include "lander.h"
#include "ground.h"

class LunarLander : public Game {

	b2World * world;
	CollisionCallback collision;

	std::set<GameObject*> lander_gos;
	std::set<b2Body*> bodies_tbd;
	std::set<b2Joint*> joints_tbd;
	b2Body* lander_core;
	b2Body* groundBody;

	Lander* lander;
	Ground* ground;

public:

	void Create(AvancezLib* system, FMOD::Studio::System* fmod_studio);
	void Update(float dt);
	void Draw();
	void Destroy();

	virtual void Receive(Message m);

private:

	void InitWorld();
	void InitLander();
};
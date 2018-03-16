#pragma once

#include "game.h"
#include "Box2D/Box2D.h"
#include "collision_callback.h"
#include "raycast_callback.h"

#include "physics_component.h"
#include "particle_component.h"
#include "camera_behaviour_component.h"

#include "lander.h"
#include "ground.h"

/* Main class for the Lunar Lander game*/
class LunarLander : public Game {

	b2World * world;
	CollisionCallback collision;

	std::set<b2Body*> bodies_tbd;	// Bodies to be destroyed next update
	std::set<b2Joint*> joints_tbd;	// Joints to be destroyed next update
	b2Body* lander_core;			
	b2Body* groundBody;

	Lander* lander;
	Ground* ground;

	bool restart = false;

public:

	void Create(AvancezLib* system, FMOD::Studio::System* fmod_studio);
	void Update(float dt);
	void Draw();
	void Destroy();

	virtual void Receive(Message m);

private:

	void Restart();
	void InitWorld();
	void InitLander();
};
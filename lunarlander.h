#pragma once

#include "game.h"
#include "Box2D/Box2D.h"
#include "collision_callback.h"
#include "raycast_callback.h"

#include "physics_component.h"
#include "particle_component.h"
#include "camera_behaviour_component.h"

#include "level_handler.h"
#include "lander.h"
#include "ground.h"

/* Main class for the Lunar Lander game*/
class LunarLander : public Game {

	CollisionCallback collision;

	std::set<b2Body*> bodies_tbd;	// Bodies to be destroyed next update
	std::set<b2Joint*> joints_tbd;	// Joints to be destroyed next update	

	b2World* world;		// The Box2D world
	LevelHandler level_handler;	// Class for handling levels

	Lander* lander;

	float fuel_left;

	bool restart = false;

public:

	void Create(AvancezLib* system, FMOD::Studio::System* fmod_studio);
	void Update(float dt);
	void Draw();
	void Destroy();

	virtual void Receive(Message m);

private:

	void Restart();
	void InitLander();
	void InitWorld();
};
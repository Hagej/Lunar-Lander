#pragma once

#include "game.h"
#include "Box2D/Box2D.h"
#include "collision_callback.h"

#include "lander.h"

class LunarLander : public Game {

	b2World * world;
	CollisionCallback collision;

	b2Body * landerBody;

	Lander* lander;

public:

	void Create(AvancezLib* system, FMOD::Studio::System* fmod_studio);
	void Update(float dt);
	void Draw();
	void Destroy();

private:

	void InitWorld();
	void InitLander();
};
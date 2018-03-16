#pragma once

#include <set>

#include "avancezlib.h"
#include "component.h"
#include "particle.h"
#include "object_pool.h"
#include "game_defs.h"
#include "system_defs.h"
#include "lander.h"
#include "camera.h"

class ParticleComponent : public Component {

	b2World* world;
	Sprite* sprite;	// Sprite used for every particle
	Camera* camera;

	ObjectPool<Particle> particles;	// Contains all particles available
	std::set<Particle*> active_particles;	// Contains all particles currently on screen and in the b2World

	std::set<b2Body*>* bodies_tbd;	// Bodies to be destroyed

	b2BodyDef def;				// Same bodydef for all particles
	b2CircleShape shape;		// Same shape for all particles
	b2FixtureDef fdef;			// Same fixturedef for all particles

	float elapsed;		// Time elapsed since last frame. 0 when not firing thrusters

public:

	void Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2World* world, std::set<b2Body*>* bodies_tbd, Camera* camera);
	void Update(float dt);

private:
	void LaunchParticle(b2Vec2 pos, float angle);
};
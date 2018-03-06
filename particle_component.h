#pragma once

#include <set>

#include "particle.h"
#include "object_pool.h"
#include "game_defs.h"
#include "component.h"
#include "lander.h"

class ParticleComponent : public Component {

	b2World* world;
	ObjectPool<Particle> * particles;
	std::set<Particle*> active_particles;

	std::set<b2Body*>* bodies_tbd;

	b2BodyDef def;
	b2FixtureDef fdef;

public:

	void Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2World* world, std::set<b2Body*>* bodies_tbd);
	
	
	void Update(float dt);

private:
	void LaunchParticle(b2Vec2 pos, b2Vec2 dir);
};
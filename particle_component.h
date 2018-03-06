#pragma once

#include <set>

#include "avancezlib.h"
#include "component.h"
#include "particle.h"
#include "object_pool.h"
#include "game_defs.h"
#include "system_defs.h"
#include "lander.h"

class ParticleComponent : public Component {

	b2World* world;
	Sprite* sprite;

	ObjectPool<Particle> particles;
	std::set<Particle*> active_particles;

	std::set<b2Body*>* bodies_tbd;

	b2BodyDef def;
	b2CircleShape shape;
	b2FixtureDef fdef;

	float elapsed;

public:

	void Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2World* world, std::set<b2Body*>* bodies_tbd);
	void Update(float dt);

private:
	void LaunchParticle(b2Vec2 pos, float angle);
};
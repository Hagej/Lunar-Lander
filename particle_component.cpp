#include "particle_component.h"
#include <time.h>

void ParticleComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2World* world, std::set<b2Body*>* bodies_tbd) {
	Component::Create(system, go, game_objects);


	Lander* lander = (Lander*)go;
	this->world = world;
	particles->Create(PARTICLE_MAX_AMOUNT);

	this->bodies_tbd = bodies_tbd;

	def.type = b2_dynamicBody;
	
	b2CircleShape shape;
	shape.m_radius = 0.5f;

	fdef.shape = &shape;

	srand(time(NULL));
}

void ParticleComponent::LaunchParticle(b2Vec2 pos, b2Vec2 dir) {
	Particle* p = particles->FirstAvailable();
	def.position = pos;
	dir *= (PARTICLE_MIN_VELOCITY + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (PARTICLE_MAX_VELOCITY - PARTICLE_MIN_VELOCITY))));
	def.linearVelocity = dir;
	p->m_body = world->CreateBody(&def);
	p->m_body->CreateFixture(&fdef);
	p->Init(PARTICLE_LIFE * static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (1.0f - PARTICLE_LIFE_VARIATION))));

	active_particles.insert(p);
}

void ParticleComponent::Update(float dt) {
	for (Particle* p : active_particles) {
		p->life_time += dt;
		if (p->life < p->life_time) {
			active_particles.erase(p);
			bodies_tbd->insert(p->m_body);
			p->m_enabled = false;
		}
	}
}

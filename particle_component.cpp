#include "particle_component.h"
#include <time.h>

void ParticleComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2World* world, std::set<b2Body*>* bodies_tbd) {
	Component::Create(system, go, game_objects);

	sprite = system->createSprite("data/particle.bmp");
	this->world = world;
	particles.Create(PARTICLE_MAX_AMOUNT);

	this->bodies_tbd = bodies_tbd;

	def.type = b2_dynamicBody;
	
	shape.m_radius = 1.0f;
	fdef.shape = &shape;
	fdef.density = 1.0f;
	fdef.restitution = 0.15f;
	fdef.filter.maskBits = 0x0004;

	srand(time(NULL));
}

void ParticleComponent::LaunchParticle(b2Vec2 pos, float angle) {
	Particle* p = particles.FirstAvailable();
	if (p != NULL) {
		pos.y -= 20.0f;
		def.position = pos;
		b2Vec2 dir;
		angle -= PARTICLE_ANGLE_VARIATION / 2.0f;
		angle += static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / PARTICLE_ANGLE_VARIATION));
		float speed = PARTICLE_MIN_VELOCITY + static_cast<float> (rand()) / static_cast<float>(RAND_MAX / (PARTICLE_MAX_VELOCITY - PARTICLE_MIN_VELOCITY));
		dir.x = cos(angle) * speed;
		dir.y = sin(angle) * speed;
		def.linearVelocity = dir;
		p->m_body = world->CreateBody(&def);
		p->m_body->CreateFixture(&fdef);
		float life_time = PARTICLE_LIFE * static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (1.0f - PARTICLE_LIFE_VARIATION)));
		p->Init(1000.0f);

		active_particles.insert(p);
	}
}

void ParticleComponent::Update(float dt) {
	std::set<Particle*> inactive;
	for (Particle* p : active_particles) {
		p->life_time += dt;
		if (p->life < p->life_time) {
			inactive.insert(p);
			bodies_tbd->insert(p->m_body);
			p->m_enabled = false;
		} else {
			sprite->draw(p->m_body->GetPosition().x, WINDOW_HEIGHT - p->m_body->GetPosition().y, p->m_body->GetAngle() - M_PI);
		}
	}
	for (Particle* p : inactive) {
		active_particles.erase(p);
	}
	Lander* lander = (Lander*)m_go;
	if (lander->IsFiring()) {
		elapsed += dt;
		int particlesThisFrame = PARTICLES_PER_SECOND * elapsed;
		for (int i = 0; i < particlesThisFrame; i++) {
			LaunchParticle(lander->GetBody()->GetPosition(), lander->GetBody()->GetAngle() - M_PI / 2.0f);
			elapsed -= 1.0f / PARTICLES_PER_SECOND;
		}
	} else {
		elapsed = 0;
	}
}

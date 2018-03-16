#include "particle_component.h"
#include <time.h>

/* Creates a particle component */
void ParticleComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2World* world, std::set<b2Body*>* bodies_tbd, Camera* camera) {
	Component::Create(system, go, game_objects);

	this->world = world;
	this->camera = camera;		// Used for rendering in the right location

	sprite = system->createSprite("data/particle.bmp");	// Same sprite used for every particle
	particles.Create(PARTICLE_MAX_AMOUNT);		// Creates all particles

	this->bodies_tbd = bodies_tbd;

	def.type = b2_dynamicBody;
	
	shape.m_radius = 1.0f;
	fdef.shape = &shape;
	fdef.density = 1.0f;
	fdef.restitution = 0.15f;
	fdef.filter.maskBits = 0x0004;		// Filter so that the particles do not collide with the lander

	srand(time(NULL));
}

/* Launches a particle at the given position in the given direction */
void ParticleComponent::LaunchParticle(b2Vec2 pos, float angle) {
	// Grabs an available particle
	Particle* p = particles.FirstAvailable();	
	if (p != NULL) {
		def.position = pos;
		b2Vec2 dir;
		// Set the angle to a random value within a viration so that all particles do not go in the exact same direction
		angle -= PARTICLE_ANGLE_VARIATION / 2.0f;
		angle += static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / PARTICLE_ANGLE_VARIATION));

		// Give the particles different speeds within a span so that they don't travel with the same velocity
		float speed = PARTICLE_MIN_VELOCITY + static_cast<float> (rand()) / static_cast<float>(RAND_MAX / (PARTICLE_MAX_VELOCITY - PARTICLE_MIN_VELOCITY));
		dir.x = cos(angle) * speed;
		dir.y = sin(angle) * speed;
		def.linearVelocity = dir;
		p->m_body = world->CreateBody(&def);
		p->m_body->CreateFixture(&fdef);

		p->Init(PARTICLE_LIFE); // TODO: Perhaps randomize life time as well?

		// Add particle to set of particles that are to be updated
		active_particles.insert(p);
	}
}

void ParticleComponent::Update(float dt) {
	// Particles that should be removed
	std::set<Particle*> inactive;
	for (Particle* p : active_particles) {
		// Add dt to life_time of particle
		p->life_time += dt;

		// If particle has exceeded its lifetime don't draw but instead remove body and game object.
		if (p->life < p->life_time) {
			inactive.insert(p);
			bodies_tbd->insert(p->m_body);
			p->m_enabled = false;
		} else {
			float32 pos_x = p->m_body->GetPosition().x;
			float32 pos_y = p->m_body->GetPosition().y;
			camera->WorldToScreen(&pos_x, &pos_y);
			sprite->draw(pos_x, pos_y, p->m_body->GetAngle());
		}
	}
	for (Particle* p : inactive) {
		active_particles.erase(p);
	}
	Lander* lander = (Lander*)m_go;
	// If the lander is firing its thrusters emit particles
	if (lander->IsFiring()) {
		elapsed += dt;
		int particlesThisFrame = PARTICLES_PER_SECOND * elapsed;
		for (int i = 0; i < particlesThisFrame; i++) {
			float angle = lander->GetBody()->GetAngle() - M_PI / 2.0f;
			b2Vec2 pos = lander->GetBody()->GetPosition();
			pos.x = pos.x + cos(angle) * 20.0f;
			pos.y = pos.y + sin(angle) * 20.0f;
			LaunchParticle(pos, angle);
			elapsed -= 1.0f / PARTICLES_PER_SECOND;
		}
	} else {
		elapsed = 0;
	}
}

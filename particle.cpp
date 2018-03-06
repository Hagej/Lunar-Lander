#include "particle.h"

void Particle::Create() {
	GameObject::Create(b2Vec2(0.1f, 0.1f));
}

void Particle::Init(float life) {
	life_time = 0;
	this->life = life;
}
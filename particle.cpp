#include "particle.h"

void Particle::Init(float life) {
	GameObject::Init();

	life_time = 0;
	this->life = life;
}
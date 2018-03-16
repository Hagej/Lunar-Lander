#include "particle.h"

/* Initiates a particle with a specified life time*/
void Particle::Init(float life) {
	GameObject::Init();

	life_time = 0;
	this->life = life;
}
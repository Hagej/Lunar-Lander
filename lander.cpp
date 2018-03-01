#include "avancezlib.h"
#include "lander.h"
#include "system_defs.h"
#include "game_defs.h"



void Lander::Create(b2Vec2 size, b2Body* body) {

	GameObject::Create(size);

	m_body = body;
	m_size = b2Vec2(LANDER_HALF_WIDTH * 2, LANDER_HALF_HEIGHT * 2);
}

int Lander::Crash() {
	is_crashing = true;
	return 0;
}

int Lander::Land() {
	return 1;
}

void Lander::Destroy() {
	Send(CRASH);
	m_body->GetWorld()->DestroyBody(m_body);
	m_body->SetUserData(NULL);
	m_body = NULL;
	this->m_enabled = false;
	GameObject::Destroy();

	
}

void LanderBehaviourComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects) {
	Component::Create(system, go, game_objects);
}

void LanderBehaviourComponent::Update(float dt) {
	if (!m_go->m_enabled) { 
		return; 
	}

	Lander* lander = (Lander *)m_go;

	if (lander->IsCrashing()) {
		lander->Destroy();
		return;
	}

	AvancezLib::KeyStatus keys;
	m_system->getKeyStatus(keys);
	lander->SetFiring(false);
	if (keys.fire) {
		lander->SetFiring(true);

		b2Body* body = lander->GetBody();
		float32 angle = body->GetAngle() + M_PI/2;
		b2Vec2 vec = b2Vec2(cos(angle), sin(angle));
		vec.Normalize();

		b2Vec2 force = b2Vec2(vec.x * LANDER_THRUST * dt, vec.y * LANDER_THRUST * dt);

		body->ApplyForceToCenter(force, true);
	}
	if (keys.left && !keys.right) {
		b2Body* body = lander->GetBody();
		body->SetTransform(body->GetPosition(), body->GetAngle() + (LANDER_ROTATION_SPEED * dt));
	}
	if (keys.right && !keys.left) {
		b2Body* body = lander->GetBody();
		body->SetTransform(body->GetPosition(), body->GetAngle() - (LANDER_ROTATION_SPEED * dt));
	}
}

void LanderRenderComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects, const char* lander_sprite, std::set<const char*>* sprites) {
	Component::Create(system, go, game_objects);

	m_default_sprite = system->createSprite(lander_sprite);
	int i = 0;
	for (const char* ch : *sprites) {
		m_sprites.insert(system->createSprite(ch));
	}
}

void LanderRenderComponent::Update(float dt) {

	if (!m_go->m_enabled) {
		return;
	}
	if (((Lander *)m_go)->IsFiring()) {
		(*(m_sprites.begin()))->draw(int(m_go->m_horizontalPosition), int(m_go->m_verticalPosition), m_go->m_angle);
	} else {
		m_default_sprite->draw(int(m_go->m_horizontalPosition), int(m_go->m_verticalPosition), m_go->m_angle);
	}

}


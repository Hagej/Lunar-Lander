#include "avancezlib.h"
#include "lander.h"
#include "system_defs.h"
#include "game_defs.h"



void Lander::Create(b2Vec2 size, b2Body* body) {

	GameObject::Create(size);

	m_body = body;
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

	if (lander->GetBody() == NULL) {
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
		body->SetAngularVelocity(body->GetAngularVelocity() * 0.9f);
		body->SetTransform(body->GetPosition(), body->GetAngle() + (LANDER_ROTATION_SPEED * dt));
	}
	if (keys.right && !keys.left) {
		b2Body* body = lander->GetBody();
		body->SetAngularVelocity(body->GetAngularVelocity() * 0.9f);
		body->SetTransform(body->GetPosition(), body->GetAngle() - (LANDER_ROTATION_SPEED * dt));
	}
}

void LanderRenderComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects, const char* lander_sprite, const char** sprites, int num_sprites) {
	Component::Create(system, go, game_objects);

	this->num_sprites = num_sprites;
	m_sprites = new Sprite* [num_sprites];

	m_default_sprite = system->createSprite(lander_sprite);
	for (int i = 0; i < num_sprites; i++) {
		m_sprites[i] = system->createSprite(sprites[i]);
	}
}

void LanderRenderComponent::Update(float dt) {

	if (!m_go->m_enabled) {
		return;
	}
	if (((Lander *)m_go)->IsFiring()) {
		b2Vec2 pos = ((Lander*)m_go)->GetBody()->GetPosition();
		m_sprites[animation]->draw(pos.x, pos.y, m_go->m_angle, m_go->GetSize().x, m_go->GetSize().y);
		animation = (animation + 1) % num_sprites;
	} else {
		m_default_sprite->draw(int(m_go->m_horizontalPosition), int(m_go->m_verticalPosition), m_go->m_angle);
	}

}


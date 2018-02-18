#include "avancezlib.h"
#include "lander.h"
#include "system_defs.h"
#include "game_defs.h"



void Lander::Create(b2Vec2 size, b2Body* body) {

	GameObject::Create(size);

	m_body = body;
	m_size = b2Vec2(LANDER_WIDTH, LANDER_HEIGHT);
}

int Lander::Crash() {
	is_crashing = true;
	this->m_enabled = false;
	return 0;
}

int Lander::Land() {
	return 1;
}

void Lander::Destroy() {
	GameObject::Destroy();
	m_body->GetWorld()->DestroyBody(m_body);
}

void LanderBehaviourComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects) {
	Component::Create(system, go, game_objects);
}

void LanderBehaviourComponent::Update(float dt) {

	if (((Lander *)m_go)->IsCrashing()) {
		((Lander *)m_go)->Destroy();
		return;
	}

	AvancezLib::KeyStatus keys;
	m_system->getKeyStatus(keys);
	if (keys.fire) {
		b2Body* body = ((Lander *)m_go)->GetBody();
		float32 angle = body->GetAngle() + M_PI/2;
		b2Vec2 vec = b2Vec2(cos(angle), sin(angle));
		vec.Normalize();

		b2Vec2 force = b2Vec2(vec.x * LANDER_THRUST * dt, vec.y * LANDER_THRUST * dt);

		body->ApplyForceToCenter(force, true);
	}
	if (keys.left && !keys.right) {
		b2Body* body = ((Lander *)m_go)->GetBody();
		body->SetTransform(body->GetPosition(), body->GetAngle() + (LANDER_ROTATION_SPEED * dt));
	}
	if (keys.right && !keys.left) {
		b2Body* body = ((Lander *)m_go)->GetBody();
		body->SetTransform(body->GetPosition(), body->GetAngle() - (LANDER_ROTATION_SPEED * dt));
	}


}
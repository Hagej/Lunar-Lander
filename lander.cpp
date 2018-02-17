#include "avancezlib.h"
#include "lander.h"
#include "system_defs.h"
#include "game_defs.h"



void Lander::Create(b2Body* body) {
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

void LanderPhysicsComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2Body* body) {
	Component::Create(system, go, game_objects);
	m_body = body;
}

void LanderPhysicsComponent::Update(float dt) {

	if (((Lander *)m_go)->IsCrashing()) {
		m_body->GetWorld()->DestroyBody(m_body);
		return;
	}

	b2Vec2 size = ((Lander *)m_go)->GetSize();
	b2Vec2 position = m_body->GetPosition();
	float32 angle = m_body->GetAngle();

	// update the state of the game object here
	m_go->m_horizontalPosition = position.x - size.x;
	m_go->m_verticalPosition = WINDOW_HEIGHT - (position.y + size.y);
	m_go->m_angle = angle * (-180 / 3.14f);
}

void LanderBehaviourComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects) {
	Component::Create(system, go, game_objects);
}

void LanderBehaviourComponent::Update(float dt) {

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
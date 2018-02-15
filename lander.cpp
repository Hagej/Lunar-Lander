#include "avancezlib.h"
#include "lander.h"


void LanderPhysicsComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2Body* body) {
	Component::Create(system, go, game_objects);
	m_body = body;
}

void LanderPhysicsComponent::Update(float dt) {

	b2Vec2 size = ((Lander *)m_go)->getSize();
	b2Vec2 position = m_body->GetPosition();
	float32 angle = m_body->GetAngle();

	// update the state of the game object here
	m_go->m_horizontalPosition = position.x - size.x;
	m_go->m_verticalPosition = WINDOW_HEIGHT - (position.y + size.y);
	m_go->m_angle = angle * (-180 / 3.14f);
}

void LanderBehaviourComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2Body* body) {
	Component::Create(system, go, game_objects);
	m_body = body;	
}

void LanderBehaviourComponent::Update(float dt) {

	AvancezLib::KeyStatus keys;
	m_system->getKeyStatus(keys);
	if (keys.fire) {
		float32 angle = m_body->GetAngle() + M_PI/2;
		float32 x = cos(angle);
		float32 y = sin(angle);

		b2Vec2 force = b2Vec2(x * LANDER_THRUST, y * LANDER_THRUST);

		m_body->ApplyForceToCenter(force, true);
	}
	if (keys.left && !keys.right) {
		m_body->SetTransform(m_body->GetPosition(), m_body->GetAngle() + (LANDER_ROTATION_SPEED * dt));
	}
	if (keys.right && !keys.left) {
		m_body->SetTransform(m_body->GetPosition(), m_body->GetAngle() - (LANDER_ROTATION_SPEED * dt));
	}
	
	
}
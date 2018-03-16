#include "physics_component.h"

void PhysicsComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2Body* body) {
	Component::Create(system, go, game_objects);
	m_body = body;
}

/* Sets the current position of the game object to be the same as the b2Body */
void PhysicsComponent::Update(float dt) {

	b2Vec2 position = m_body->GetPosition();
	float32 angle = m_body->GetAngle();

	// update the state of the game object here
	m_go->m_horizontalPosition = position.x;
	m_go->m_verticalPosition = position.y;
	m_go->m_angle = angle * (-180 / 3.14f);
}
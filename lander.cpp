#include "lander.h"


void LanderPhysicsComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, b2Body* body) {
	Component::Create(system, go, game_objects);
	m_body = body;
}

void Update(float dt) {

	b2Vec2 size = ((Lander *)m_go)->getSize();
	b2Vec2 position = m_body->GetPosition();
	float32 angle = m_body->GetAngle();

	// update the state of the game object here
	m_go->m_horizontalPosition = position.x - size.x;
	m_go->m_verticalPosition = WINDOW_HEIGHT - (position.y + size.y);
	m_go->m_angle = angle * (-180 / 3.14f);
}
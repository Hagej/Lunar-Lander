#include "ground.h"

void Ground::Create(b2Vec2 size, b2Body* body) {
	GameObject::Create(size);
	m_body = body;
}


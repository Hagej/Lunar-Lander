#pragma once

#include "Box2D\Box2D.h"
#include "game_object.h"

class Ground : public GameObject {

	b2Body* m_body;

public: 
	void Create(b2Vec2 size, b2Body* body);

	inline b2Body* GetBody() { return m_body; }


};
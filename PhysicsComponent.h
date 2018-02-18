#pragma once

#include "system_defs.h"

#include "game_object.h"
#include "component.h"
#include "Box2D\Box2D.h"

class PhysicsComponent : public Component {

	b2Body* m_body;

public:
	virtual void Create(AvancezLib * system, GameObject *go, std::set<GameObject*>* gameObjects, b2Body *body);
	virtual void Update(float dt);
};
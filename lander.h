#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"

class Lander : public GameObject {

	b2Vec2 m_size;

public:

	inline b2Vec2 getSize() { return m_size; }
};

class LanderPhysicsComponent : public Component {

	b2Body* m_body;

public:
	virtual void Create(AvancezLib * system, GameObject *go, std::set<GameObject*>* gameObjects, b2Body *body);
	virtual void Update(float dt);
};

class LanderBehaviourComponent : public Component {

	b2Body* m_body;

public:

	virtual void Create(AvancezLib * system, GameObject* go, std::set<GameObject*>* gameObjects, b2Body* body);
	virtual void Update(float dt);

};

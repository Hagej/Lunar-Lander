#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"

class Lander : public GameObject {

	b2Body* m_body;
	b2Vec2 m_size;

	bool is_crashing = false;

public:

	void Create(b2Body* body);

	inline b2Vec2 GetSize() { return m_size; }
	inline b2Body* GetBody() { return m_body; }
	inline bool IsCrashing() { return is_crashing; }
	int Land();
	int Crash();

};

class LanderPhysicsComponent : public Component {

	b2Body* m_body;

public:
	virtual void Create(AvancezLib * system, GameObject *go, std::set<GameObject*>* gameObjects, b2Body *body);
	virtual void Update(float dt);
};

class LanderBehaviourComponent : public Component {

public:

	virtual void Create(AvancezLib * system, Lander* go, std::set<GameObject*>* gameObjects);
	virtual void Update(float dt);

};

#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"

class Lander : public GameObject {

	b2Body* m_body;

	bool is_crashing = false;

public:

	void Create(b2Vec2 size, b2Body* body);

	inline b2Body* GetBody() { return m_body; }
	inline bool IsCrashing() { return is_crashing; }
	int Land();
	int Crash();
	void Destroy();

};

class LanderBehaviourComponent : public Component {

public:

	virtual void Create(AvancezLib * system, Lander* go, std::set<GameObject*>* gameObjects);
	virtual void Update(float dt);

};

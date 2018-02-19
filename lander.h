#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"

class Lander : public GameObject {

	b2Body* m_body;

	bool is_crashing = false;
	bool is_firing = false;

public:

	void Create(b2Vec2 size, b2Body* body);

	inline b2Body* GetBody() { return m_body; }
	inline bool IsCrashing() { return is_crashing; }
	inline void SetFiring(bool firing) { is_firing = firing; }
	inline bool IsFiring() { return is_firing; }
	int Land();
	int Crash();
	void Destroy();

};

class LanderBehaviourComponent : public Component {

public:

	virtual void Create(AvancezLib * system, Lander* go, std::set<GameObject*>* gameObjects);
	virtual void Update(float dt);

};


class LanderRenderComponent : public Component {

	Sprite* m_default_sprite;
	std::set<Sprite *> m_sprites;


public:

	virtual void Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects, const char* lander_sprite, std::set<const char*>* sprites);
	virtual void Update(float dt);
};
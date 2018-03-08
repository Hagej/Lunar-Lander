#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"

class Lander : public GameObject {

	b2Body* m_body;

	bool is_firing = false;


public:

	void Create(b2Vec2 size, b2Body* body);

	inline b2Body* GetBody() { return m_body; }
	inline void SetFiring(bool firing) { is_firing = firing; }
	inline bool IsFiring() { return is_firing; }
	void Land();
	void Crash();

};

class LanderBehaviourComponent : public Component {

	float hover_time;

public:

	virtual void Create(AvancezLib * system, Lander* go, std::set<GameObject*>* gameObjects);
	virtual void Update(float dt);

};


class LanderRenderComponent : public Component {

	Sprite* m_default_sprite;
	Sprite** m_sprites;

	int animation;
	int num_sprites;


public:

	virtual void Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects, const char* lander_sprite, const char** sprites, int num_sprites);
	virtual void Update(float dt);
};
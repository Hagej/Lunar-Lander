#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"
#include "raycast_callback.h"

class Lander : public GameObject {

	b2Body* m_body;				// The main body of the lander
	bool is_firing = false;		// TODO: Change to status enum instead?
	float m_altitude;

public:

	void Create(b2Vec2 size, b2Body* body);

	inline b2Body* GetBody() { return m_body; }
	inline float GetAltitude() { return m_altitude; }
	inline void SetAltitude(float altitude) { m_altitude = altitude; }
	inline bool IsFiring() { return is_firing; }
	inline void SetFiring(bool firing) { is_firing = firing; }
	void Land();
	void Crash();

	int AttachedBodies();

private: 

	void AttachedBodies(b2Body* body, std::set<b2Body*>*bodies);

};

class LanderBehaviourComponent : public Component {

	RaysCastCallback raycast;
	
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
#pragma once

#include "Box2D\Box2D.h"
#include "component.h"
#include "game_object.h"
#include "raycast_callback.h"

class Lander : public GameObject {

	b2Body* m_body;					// The main body of the lander
	std::set<b2Body*> m_legs; // The bodies of the legs of the lander

	bool is_firing = false;		// TODO: Change to status enum instead?
	float m_altitude;
	float m_fuel;


public:

	void Create(b2Vec2 size, b2World* world);

	inline b2Body* GetBody() { return m_body; }
	inline std::set<b2Body*> GetLegs() { return m_legs; }
	inline float GetAltitude() { return m_altitude; }

	inline void SetAltitude(float altitude) { m_altitude = altitude; }
	inline bool IsFiring() { return is_firing; }
	inline void SetFiring(bool firing) { is_firing = firing; }

	inline float GetFuel() { return m_fuel; }
	void ReduceFuel(float amount);

	void Land();
	void Crash();
	void OutOfFuel();

	void Destroy();

	int AttachedBodies();

private: 

	void InitBody(b2World* world, b2Vec2 pos);
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
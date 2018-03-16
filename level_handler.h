#pragma once

#include "game_object.h"
#include "collision_callback.h"
#include "component.h"

class LevelHandler : public GameObject {

	CollisionCallback collision;
	
	b2BodyDef groundDef;
	b2Body* cur_level;


	b2FixtureDef groundFixtureDef;
	b2EdgeShape* slice = new b2EdgeShape();

public:
	
	b2World* m_world;

	void Create(b2World* world, std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd);

	inline b2Body* GetLevel() { return cur_level; }

	void ClearWorld();
	void GenerateLevel(const int width, const int height);

};

class LevelComponent : public Component {

	Camera* m_camera;
	b2Body* m_level;

	Sprite* sprite;

public:

	void Create(AvancezLib* system, LevelHandler* go, std::set<GameObject*>* game_objects, Camera* camera);

	void Update(float dt);
};
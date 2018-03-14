#pragma once

#include <set>
#include "object_pool.h"
#include "camera.h"

class GameObject;
class AvancezLib;
class Sprite;

class Component
{
protected:
	AvancezLib * m_system;	// used to access the system
	GameObject * m_go;		// the game object this component is part of
	std::set<GameObject*> * m_game_objects;	// the global container of game objects

public:
	virtual ~Component() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects);
	
	virtual void Init() {}
	virtual void Update(float dt) = 0;
	virtual void Receive(int message) {}
	virtual void Destroy() {}
};


class RenderComponent : public Component
{
	Sprite* m_sprite;
	Camera* m_camera;

public:

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, Camera* camera, const char * sprite_name);
	virtual void Update(float dt);
	virtual void Destroy();

	Sprite * GetSprite() { return m_sprite; }
};


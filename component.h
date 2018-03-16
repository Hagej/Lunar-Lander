#pragma once

#include <set>

class GameObject;
class AvancezLib;
class Sprite;

class Component
{
protected:
	AvancezLib * m_system;	// Used to access the system
	GameObject * m_go;		// The game object this component is part of
	std::set<GameObject*> * m_game_objects;	// A container of all the game objects

public:
	virtual ~Component() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects);
	
	virtual void Init() {}
	virtual void Update(float dt) = 0;	// Must be implemented in subclasses 
	virtual void Receive(int message) {}
	virtual void Destroy() {}
};


#include "camera.h"

/* Base component for rendering. Uses a camera to know where to render the sprite in the window */
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


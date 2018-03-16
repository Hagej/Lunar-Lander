// GameObject represents objects which moves are drawn
#pragma once
#include <vector>

#include "Box2D\Box2D.h"

enum Message { CRASH, LAND, GAME_OVER, NO_MSG };

class Component;

class GameObject
{
protected:
	std::vector<GameObject*> m_receivers;
	std::vector<Component*> m_components;


public:
	double m_horizontalPosition;	// x position
	double m_verticalPosition;		// y position
	float m_angle;					// angle of rotation in degrees
	bool m_enabled;					
	b2Vec2 m_size;					// Size of Sprite being drawn (Not neccesarily same as bounding box)

	virtual ~GameObject();

	virtual void Create(b2Vec2 size);
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);
};
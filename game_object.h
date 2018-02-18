// GameObject represents objects which moves are drawn
#pragma once
#include <vector>

#include "Box2D\Box2D.h"

enum Message { HIT, ALIEN_HIT, GAME_OVER, LEVEL_WIN, NO_MSG };

class Component;

class GameObject
{
protected:
	std::vector<GameObject*> m_receivers;
	std::vector<Component*> m_components;

	b2Vec2 m_size;

public:
	double m_horizontalPosition;
	double m_verticalPosition;
	float m_angle; // angle of rotation in degrees
	bool m_enabled;

	virtual ~GameObject();

	virtual void Create(b2Vec2 size);
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);

	inline b2Vec2 GetSize() { return m_size; }
};
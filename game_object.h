// GameObject represents objects which moves are drawn
#pragma once
#include <vector>

enum Message { HIT, ALIEN_HIT, GAME_OVER, LEVEL_WIN, NO_MSG };

class Component;

class GameObject
{
protected:
	std::vector<GameObject*> m_receivers;
	std::vector<Component*> m_components;

public:
	double m_horizontalPosition;
	double m_verticalPosition;
	float m_angle; // angle of rotation in degrees
	bool m_enabled;

	virtual ~GameObject();

	virtual void Create();
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);
};
#include "game_object.h"
#include "component.h"
#include "avancezlib.h"

void GameObject::Create(b2Vec2 size)
{
	SDL_Log("GameObject::Create");

	m_size = size;
	m_enabled = false;
	m_angle = 0;
}

void GameObject::AddComponent(Component * component)
{
	m_components.push_back(component);
}


void GameObject::Init()
{
	SDL_Log("GameObject::Init");

	for (auto it : m_components)
		it->Init();

	m_enabled = true;
}

void GameObject::Update(float dt)
{
	if (!m_enabled)
		return;

	for (auto it : m_components)
		it->Update(dt);
}

void GameObject::Destroy()
{
	for (auto it : m_components)
		it->Destroy();
}

GameObject::~GameObject()
{
	SDL_Log("GameObject::~GameObject");
}

void GameObject::AddReceiver(GameObject * go)
{
	m_receivers.push_back(go);
}

void GameObject::Send(Message m)
{
	for (auto receiver : m_receivers)
	{
		if (!receiver->m_enabled)
			continue;

		receiver->Receive(m);
	}
}

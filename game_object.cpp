#include "game_object.h"
#include "component.h"
#include "avancezlib.h"
#include "system_defs.h"

/* Default create function of game objects. Sets size */
void GameObject::Create(b2Vec2 size)
{
	LOG("GameObject::Create");
	m_size = size;
	m_enabled = false;
	m_angle = 0;
}

/* Adds a component to the game object */
void GameObject::AddComponent(Component * component)
{
	m_components.push_back(component);
}

/* Initiates all component connected to the game object and enables the game object */
void GameObject::Init()
{
	LOG("GameObject::Init");
	for (auto it : m_components)
		it->Init();

	m_enabled = true;
}

/* Updates all components if enabled */
void GameObject::Update(float dt)
{
	if (!m_enabled)
		return;

	for (auto it : m_components)
		it->Update(dt);
}

/* Destroys all components */
void GameObject::Destroy()
{
	for (auto it : m_components)
		it->Destroy();
}

GameObject::~GameObject()
{
	LOG("GameObject::~GameObject");
}

/* Add game object which recievs messages from this game object */
void GameObject::AddReceiver(GameObject * go)
{
	m_receivers.push_back(go);
}

/* Send message to all enabled receivers */
void GameObject::Send(Message m)
{
	for (auto receiver : m_receivers)
	{
		if (!receiver->m_enabled)
			continue;

		receiver->Receive(m);
	}
}

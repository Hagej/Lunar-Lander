#include "component.h"
#include "game_object.h"
#include "avancezlib.h"

void Component::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects)
{
	m_go = go;
	m_system = system;
	m_game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, const char * sprite_name)
{
	Component::Create(system, go, game_objects);

	sprite = system->createSprite(sprite_name);
}

void RenderComponent::Update(float dt)
{
	if (!m_go->m_enabled)
		return;

	if (sprite)
		sprite->draw(int(m_go->m_horizontalPosition), int(m_go->m_verticalPosition), m_go->m_angle);
}

void RenderComponent::Destroy()
{
	if (sprite != NULL)
		sprite->destroy();
	sprite = NULL;
}


void CollideComponent::Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<GameObject> * coll_objects)
{
	Component::Create(system, go, game_objects);
	this->coll_objects = coll_objects;
}


void CollideComponent::Update(float dt)
{
	for (auto go0 : coll_objects->m_pool)
	{
		if (go0->m_enabled)
		{
			if ((go0->m_horizontalPosition > m_go->m_horizontalPosition - 10) &&
				(go0->m_horizontalPosition < m_go->m_horizontalPosition + 10) &&
				(go0->m_verticalPosition   > m_go->m_verticalPosition - 10) &&
				(go0->m_verticalPosition   < m_go->m_verticalPosition + 10))
			{
				m_go->Receive(HIT);
				go0->Receive(HIT);
			}
		}
	}
}

#include "component.h"
#include "game_object.h"
#include "avancezlib.h"

void Component::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects)
{
	m_go = go;
	m_system = system;
	m_game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, Camera* camera, const char * sprite_name)
{
	Component::Create(system, go, game_objects);

	m_sprite = system->createSprite(sprite_name);
	m_camera = camera;
}

void RenderComponent::Update(float dt)
{
	if (!m_go->m_enabled)
		return;

	if (m_sprite)
		m_camera->draw(m_go, m_sprite);
}

void RenderComponent::Destroy()
{
	if (m_sprite != NULL)
		m_sprite->destroy();
	m_sprite = NULL;
}

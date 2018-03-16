#include "camera_behaviour_component.h"
#include "lander.h"
#include "avancezlib.h"

void CameraBehaviourComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, Camera* camera) {
	Component::Create(system, go, game_objects);
	m_camera = camera;
}

void CameraBehaviourComponent::Update(float dt) {
	Lander* lander = (Lander*)m_go;

	if (m_camera->getZoom() != ZOOM_AMOUNT) {
		if (lander->distance_to_ground <= 300) {
			m_camera->setPosition(lander->m_horizontalPosition, lander->m_verticalPosition - 150);
			m_camera->setZoom(ZOOM_AMOUNT);
		}
	}
	else {
		if (lander->distance_to_ground >= 450) {
			m_camera->setPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
			m_camera->setZoom(0.5f);
		}
		SDL_Rect viewport = m_camera->getViewport();
		int x = 0, y = 0;

		/* If the lander gets close to the edge of the screen, pan the camera in that direction */
		if (lander->GetBody()->GetPosition().x > viewport.x + viewport.w - 50) {
			x = 1;
		}
		if (lander->GetBody()->GetPosition().x < viewport.x - viewport.w + 50) {
			x = -1;
		}
		if (lander->GetBody()->GetPosition().y > viewport.y + viewport.h - 50) {
			y = 1;
		}
		if (lander->GetBody()->GetPosition().y < viewport.y - viewport.h + 50) {
			y = -1;
		}
		m_camera->pan(x, y);
	}
}
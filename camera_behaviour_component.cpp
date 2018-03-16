#include "camera_behaviour_component.h"
#include "lander.h"
#include "avancezlib.h"
#include "game_defs.h"

/* Component for controling the behaviour of the camera */
void CameraBehaviourComponent::Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, Camera* camera) {
	Component::Create(system, go, game_objects);
	LOG("CameraBehaviourComponent::Create");
	m_camera = camera;
}

/* Update method. Moves the camera depending on the location of the given game object */
void CameraBehaviourComponent::Update(float dt) {
	Lander* lander = (Lander*)m_go;

	if (m_camera->GetZoom() != ZOOM_AMOUNT) {
		/* If the game object gets close enough to the ground, zoom in */
		if (lander->GetAltitude() <= 300) {
			m_camera->SetPosition(lander->m_horizontalPosition, lander->m_verticalPosition - 150);
			m_camera->SetZoom(ZOOM_AMOUNT);
		}
	}
	else {
		/* If the game object gets to far away from the ground again, zoom out to full map */
		if (lander->GetAltitude() >= 450) {
			m_camera->SetPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
			m_camera->SetZoom(0.5f);
		}
		SDL_Rect viewport = m_camera->GetViewport();
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
		m_camera->Pan(x, y);
	}
}
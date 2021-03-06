#pragma once

#include "component.h"

class CameraBehaviourComponent : public Component {

	Camera* m_camera;

public:

	void Create(AvancezLib* system, GameObject* go, std::set<GameObject*>* game_objects, Camera* camera);
	void Update(float dt);

};
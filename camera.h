#pragma once

#include "Box2D\Box2D.h"
#include "avancezlib.h"
#include "system_defs.h"
#include "game_object.h"

class Camera {

	SDL_Rect m_viewport;
	float m_zoom;

	

public:

	Camera(int x, int y, int w, int h);
	void pan(const int dx = 1, const int dy = 1);
	void setZoom(const float zoom = 1.0f);
	void setPosition(const b2Vec2 position);
	void setPosition(const int x, const int y);
	void draw(GameObject* go, Sprite* sprite);

private:

	void worldToScreen(float32* x, float32* y);

};
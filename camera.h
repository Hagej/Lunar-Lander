#pragma once

#include "system_defs.h"
#include "Box2D\Box2D.h"
#include "avancezlib.h"

class GameObject;

class Camera {

	SDL_Rect m_viewport;

	float m_zoom;

public:

	Camera(int x, int y, int w, int h);
	void pan(const int dx = 1, const int dy = 1);
	inline float getZoom() { return m_zoom; }
	void setZoom(const float zoom = 1.0f);
	void setPosition(const b2Vec2 position);
	void setPosition(const int x, const int y);
	inline SDL_Rect getViewport() { return m_viewport; }
	void draw(GameObject* go, Sprite* sprite);

	void worldToScreen(float32* x, float32* y);

};


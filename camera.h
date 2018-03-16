#pragma once

#include "system_defs.h"
#include "Box2D\Box2D.h"
#include "avancezlib.h"

class GameObject;

class Camera {

	SDL_Rect m_viewport;	// Contains the position of the camera and the half-width and half-height
	float m_zoom;			// Used for increasing/decreasing the size of sprites

public:

	Camera(int x, int y, int w, int h);

	void Pan(const int dx = 1, const int dy = 1);
	
	inline float GetZoom() { return m_zoom; }
	void SetZoom(const float zoom = 1.0f);
	void Zoom(const int dz);

	void SetPosition(const b2Vec2 position);
	void SetPosition(const int x, const int y);

	inline SDL_Rect GetViewport() { return m_viewport; }

	void Draw(GameObject* go, Sprite* sprite);

	void WorldToScreen(float32* x, float32* y);

};


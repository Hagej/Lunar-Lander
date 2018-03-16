#pragma once

#include "camera.h"
#include "game_object.h"

/* Construct a camera object which determines where game objects are drawn on screen */
Camera::Camera(int x, int y, int w, int h) {
	m_viewport.x = x;
	m_viewport.y = y;
	m_viewport.w = w;
	m_viewport.h = h;

	m_zoom = WINDOW_WIDTH / (m_viewport.w*2);
}

/* Move the camera along the 2D plane */
void Camera::Pan(const int dx, const int dy) {
	m_viewport.x += dx;
	m_viewport.y += dy;
}

/* Set the zoom of the camera. Automatically changes the viewport */
void Camera::SetZoom(const float zoom) {
	m_zoom = zoom;
	m_viewport.w = (WINDOW_WIDTH/m_zoom)/2;
	m_viewport.h = (WINDOW_HEIGHT/m_zoom)/2;
}

void Camera::Zoom(const int dz) {
	m_viewport.h += dz * (WINDOW_HEIGHT / WINDOW_WIDTH);
	m_viewport.w += dz * (WINDOW_WIDTH / WINDOW_HEIGHT);
}

/* Directly set the position of the camera to the values of a b2Vec2 */
void Camera::SetPosition(const b2Vec2 position) {
	m_viewport.x = position.x;
	m_viewport.y = position.y;
}

/* Directly set the position of the camera */
void Camera::SetPosition(const int x, const int y) {
	m_viewport.x = x;
	m_viewport.y = y;
}

void Camera::WorldToScreen(float32* x, float32* y) {
	*x -= m_viewport.x;		// x position relative to the camera				
	*x *= m_zoom;			// Modify according to zoom
	*x += WINDOW_WIDTH/2.0f;	// Position relative to screen

	*y -= m_viewport.y;			// y position relative to the camera
	*y *= m_zoom;				// Modify according to zoom
	*y += WINDOW_HEIGHT/2.0f;	// Position relative to screen
	*y = WINDOW_HEIGHT - *y;	// Invert y-value to SDL coordinates
}

/* Draws the given GameObject at the right location on the screen */
void Camera::Draw(GameObject* go, Sprite* sprite) {
	float width = go->m_size.x * m_zoom;
	float height = go->m_size.y * m_zoom;
	b2Vec2 pos;
	pos.x = go->m_horizontalPosition;
	pos.y = go->m_verticalPosition;
	if (pos.x + width/2 < (m_viewport.x - m_viewport.w)
		|| pos.x - width/2 > (m_viewport.x + m_viewport.w)
		|| pos.y + height/2 < (m_viewport.y - m_viewport.h)
		|| pos.y - height/2 > (m_viewport.y + m_viewport.h)) {
		return;
	}
	WorldToScreen(&pos.x, &pos.y);
	pos.x -= width / 2.0f;				// To get the upper right corner of the object
	pos.y -= height / 2.0f;				// Subtract as SDL has its origo in the upper left corner

	
	sprite->draw(pos.x, pos.y, go->m_angle, go->m_size.x * m_zoom, go->m_size.y * m_zoom);
}



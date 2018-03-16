#pragma once

#include "camera.h"
#include "game_object.h"

Camera::Camera(int x, int y, int w, int h) {
	m_viewport.x = x;
	m_viewport.y = y;
	m_viewport.w = w;
	m_viewport.h = h;

	m_zoom = WINDOW_WIDTH / (m_viewport.w*2);
}

void Camera::pan(const int dx, const int dy) {
	m_viewport.x += dx;
	m_viewport.y += dy;
}

void Camera::setZoom(const float zoom) {
	m_zoom = zoom;
	m_viewport.w = (WINDOW_WIDTH/m_zoom)/2;
	m_viewport.h = (WINDOW_HEIGHT/m_zoom)/2;
}

void Camera::setPosition(const b2Vec2 position) {
	m_viewport.x = position.x;
	m_viewport.y = position.y;
}
void Camera::setPosition(const int x, const int y) {
	m_viewport.x = x;
	m_viewport.y = y;
}

void Camera::worldToScreen(float32* x, float32* y) {
	*x -= m_viewport.x;		// x position relative to the camera				
	*x *= m_zoom;			// Modify according to zoom
	*x += WINDOW_WIDTH/2.0f;	// Position relative to screen

	*y -= m_viewport.y;			// y position relative to the camera
	*y *= m_zoom;				// Modify according to zoom
	*y += WINDOW_HEIGHT/2.0f;	// Position relative to screen
	*y = WINDOW_HEIGHT - *y;	// Invert y-value to SDL coordinates
}

/* Draws the given GameObject at the right location on the screen */
void Camera::draw(GameObject* go, Sprite* sprite) {
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
	worldToScreen(&pos.x, &pos.y);
	pos.x -= width / 2.0f;				// To get the upper right corner of the object
	pos.y -= height / 2.0f;				// Subtract as SDL has its origo in the upper left corner

	
	sprite->draw(pos.x, pos.y, go->m_angle, go->m_size.x * m_zoom, go->m_size.y * m_zoom);
}



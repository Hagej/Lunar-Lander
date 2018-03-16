#pragma once

#include "Box2D\Box2D.h"

/* Callback class for raycasts */
class RaysCastCallback : public b2RayCastCallback
{
public:
	RaysCastCallback() : m_fixture(NULL) {}

	/* Returns the nearest point of intersection on the ground object */
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
		if (fixture->GetBody()->GetUserData() == (void*)-1) {
			fraction = 0;	// Stops when the ground (user data -1) has been found
		} else {
			fraction = 1;
		}
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		return fraction;
	}

	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;

};

#pragma once

#include "Box2D\Box2D.h"
#include "lander.h"

// TODO: Remove this include
#include <string>

class CollisionCallback : public b2ContactListener {

	void BeginContact(b2Contact* contact) {

		SDL_Log("Crashtesting commence!");

		b2Body* body = contact->GetFixtureA()->GetBody();
		void* bodyUserData = body->GetUserData();

		if (bodyUserData) {

			Lander* lander = static_cast<Lander*>(bodyUserData);
			if (lander->m_enabled) {
				float32 vel = lander->GetBody()->GetLinearVelocity().Length();
				if (vel > LANDER_CRASH_THRESHOLD) {
					SDL_Log("Lander crashed");
					lander->Crash();
				}
				else {
					lander->Land();
				}
			}
			
		}

		body = contact->GetFixtureB()->GetBody();
		bodyUserData = body->GetUserData();

		if (bodyUserData) {
			Lander* lander = static_cast<Lander*>(bodyUserData);
			if (lander->m_enabled) {
				float32 vel = lander->GetBody()->GetLinearVelocity().Length();
				if (vel > LANDER_CRASH_THRESHOLD) {
					SDL_Log("Lander crashed");
					lander->Crash();
				}
				else {
					lander->Land();
				}
			}
		}
	}
};
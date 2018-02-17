#pragma once

#include "Box2D\Box2D.h"
#include "lander.h"


class CollisionCallback : public b2ContactListener {

	void BeginContact(b2Contact* contact) {

		SDL_Log("Crashtesting commence!");

		b2Body* body = contact->GetFixtureA()->GetBody();
		void* bodyUserData = body->GetUserData();

		if (bodyUserData) {
			if (contact->GetManifold()->points->normalImpulse > LANDER_CRASH_THRESHOLD) {
				static_cast<Lander*>(bodyUserData)->Crash();
				delete &body;
			} else {
				static_cast<Lander*>(bodyUserData)->Land();
			}
		}
	}

	void PreSolve(b2Contact* contact, const b2Manifold* old_manifold) {

		

	}

};
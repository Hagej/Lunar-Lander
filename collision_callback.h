#pragma once

#include "Box2D\Box2D.h"
#include <set>

/* Callback class for collision detection */
class CollisionCallback : public b2ContactListener {

	std::set<b2Body*>* bodies_tbd; // Bodies to be destroyed
	std::set<b2Joint*>* joints_tbd; // Joints to be destroyed

public:

	void Init(std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd);

private:

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};
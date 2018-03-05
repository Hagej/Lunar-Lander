#pragma once

#include "system_defs.h"

#include "Box2D\Box2D.h"
#include "game_defs.h"
#include "SDL.h"
#include <set>


class CollisionCallback : public b2ContactListener {

	std::set<b2Body*>* bodies_tbd;
	std::set<b2Joint*>* joints_tbd;

public:

	void Init(std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd);

private:

	void BeginContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

};
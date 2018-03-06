#include "collision_callback.h"

void CollisionCallback::Init(std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd) {
	this->bodies_tbd = bodies_tbd;
	this->joints_tbd = joints_tbd;
}

void CollisionCallback::BeginContact(b2Contact* contact) { }

void CollisionCallback::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	std::set<b2Body*> bodies;
	bodies.insert(contact->GetFixtureA()->GetBody());
	bodies.insert(contact->GetFixtureB()->GetBody());

	for (b2Body* b : bodies) {
		int bodyUserData = (int)b->GetUserData();
		switch (bodyUserData) {
			case 1:	// Lander core has collided
				if (contact->GetManifold()->points[0].normalImpulse > LANDER_CRASH_THRESHOLD) {
					bodies_tbd->insert(b);
				}
				break;
			case 2: // A lander leg has collided
			{
				b2JointEdge * joints = b->GetJointList();
				while (joints != NULL) {
					b2Vec2 forceVec = joints->joint->GetReactionForce(1.0f / PHYSICS_TIME_STEP);
					float force = forceVec.LengthSquared();
#if LOG
					SDL_Log("Leg has collided with force: %d", (int)force);
#endif
					if (force > LANDER_BREAK_THRESHOLD) {
#if LOG
						SDL_Log("Leg broke");
#endif
						joints_tbd->insert(joints->joint);
					}
					joints = joints->next;
				}
			}
				break;
			default:
				break;
		}
	}
}
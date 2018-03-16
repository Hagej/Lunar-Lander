#include "collision_callback.h"

#include "system_defs.h"
#include "game_defs.h"

/* Initialize the callback by giving references to sets containing what's to be destroyed */
void CollisionCallback::Init(std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd) {
	LOG("CollisionCallback::Init");
	this->bodies_tbd = bodies_tbd;
	this->joints_tbd = joints_tbd;
}

void CollisionCallback::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	std::set<b2Body*> bodies;
	bodies.insert(contact->GetFixtureA()->GetBody());
	bodies.insert(contact->GetFixtureB()->GetBody());

	for (b2Body* b : bodies) {
		int bodyUserData = (int)b->GetUserData();
		switch (bodyUserData) {
			case 1:	// Lander core has collided
				// Crash lander if impact is too high
				if (contact->GetManifold()->points[0].normalImpulse > LANDER_CRASH_THRESHOLD) {
					bodies_tbd->insert(b);	
				}
				break;
			case 2: // A lander leg has collided
			{
				b2JointEdge * joints = b->GetJointList();
				while (joints != NULL) {
					// Get the amount of force applied on the joint over a second
					b2Vec2 forceVec = joints->joint->GetReactionForce(1.0f / PHYSICS_TIME_STEP);
					float force = forceVec.LengthSquared();
					// Remove joint of the force is too high
					if (force > LANDER_BREAK_THRESHOLD) {
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

void CollisionCallback::BeginContact(b2Contact* contact) {}
void CollisionCallback::EndContact(b2Contact* contact) {}

void CollisionCallback::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
#include "collision_callback.h"

void CollisionCallback::Init(std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd) {
	this->bodies_tbd = bodies_tbd;
	this->joints_tbd = joints_tbd;
}

void CollisionCallback::BeginContact(b2Contact* contact){
	/*b2Body* bodyA = contact->GetFixtureA()->GetBody();
	int bodyAUserData = (int)bodyA->GetUserData();

	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	int bodyBUserData = (int)bodyB->GetUserData();

	SDL_Log("Crashtesting commence! %d %d", bodyAUserData, bodyBUserData);

	if (bodyAUserData == 2) {
		SDL_Log("Leg has been struck");
		b2JointEdge* joints = bodyA->GetJointList();
		while (joints != NULL) {
			b2Vec2 forceVec = joints->joint->GetReactionForce(1.0f / PHYSICS_TIME_STEP);
			float force = forceVec.LengthSquared();
			SDL_Log("Force: %d", (int)force);
			if (force > LANDER_BREAK_THRESHOLD) {
				SDL_Log("Leg broke");
				joints_tbd->insert(joints->joint);
			}
			joints = joints->next;
		}
	}
	else if (bodyBUserData == 2) {
		SDL_Log("Leg has been struck");
		b2JointEdge* joints = bodyB->GetJointList();
		while (joints != NULL) {
			b2Vec2 forceVec = joints->joint->GetReactionForce(1.0f / PHYSICS_TIME_STEP);
			float32 force = forceVec.LengthSquared();
			SDL_Log("Force: %d", (int)force);
			if (force > LANDER_BREAK_THRESHOLD) {
				SDL_Log("Leg broke");
				joints_tbd->insert(joints->joint);
			}
			joints = joints->next;
		}
	}*/
}

void CollisionCallback::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	int bodyAUserData = (int)bodyA->GetUserData();

	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	int bodyBUserData = (int)bodyB->GetUserData();
#if LOG
	SDL_Log("Crashtesting commence! %d %d", bodyAUserData, bodyBUserData);
#endif
	if (bodyAUserData == 2) {
#if LOG
		SDL_Log("Leg has been struck");
#endif
		b2JointEdge* joints = bodyA->GetJointList();
		while (joints != NULL) {
			b2Vec2 forceVec = joints->joint->GetReactionForce(1.0f / PHYSICS_TIME_STEP);
			float force = forceVec.LengthSquared();
#if LOG
			SDL_Log("Force: %d", (int)force);
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
	else if (bodyBUserData == 2) {
#if LOG
		SDL_Log("Leg has been struck");
#endif
		b2JointEdge* joints = bodyB->GetJointList();
		while (joints != NULL) {
			b2Vec2 forceVec = joints->joint->GetReactionForce(1.0f / PHYSICS_TIME_STEP);
			float32 force = forceVec.LengthSquared();

			SDL_Log("Force: %d", (int)force);

			if (force > LANDER_BREAK_THRESHOLD) {
#if LOG
				SDL_Log("Leg broke");
#endif
				joints_tbd->insert(joints->joint);
			}
			joints = joints->next;
		}
	}
}
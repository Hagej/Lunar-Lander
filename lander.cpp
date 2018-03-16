#include "avancezlib.h"
#include "lander.h"
#include "system_defs.h"
#include "game_defs.h"


/* Create lander game object. */
void Lander::Create(b2Vec2 size, b2Body* body) {

	GameObject::Create(size);
	LOG("Lander::Create");
	m_body = body;
}

/* Method for when the lander has crashed */
void Lander::Crash() {
	Send(CRASH);
	this->m_enabled = false;
	GameObject::Destroy();
}

/* Method for when the lander has landed successfully */
void Lander::Land() {
	Send(LAND);
}

/* Recursive method for checking the amount of bodies attached to the lander */
int Lander::AttachedBodies() {
	std::set<b2Body*> bodies;			// Set of bodies that are attached
	bodies.insert(m_body);				// Insert lander core
	AttachedBodies(m_body, &bodies);	// Start recursion
	return bodies.size();
}

void Lander::AttachedBodies(b2Body* body, std::set<b2Body*>* bodies) {
	// No body on the other end of a joint
	if (body == NULL) {
		return;	
	}
	// No additional bodies attached to this body (Should only happen if the lander has no legs left)
	else if (body->GetJointList() == NULL) {
		return;
	}
	else {
		b2JointEdge* edge = body->GetJointList();
		while (edge != NULL) {
			if (bodies->find(edge->other) == bodies->end()) {	// If the body attached to the joint is not allready found
				bodies->insert(edge->other);					// Insert body on the other end of the joint
				AttachedBodies(edge->other, bodies);			// Call recursion on that body
			}
			edge = edge->next;
		}
	}
}

/* Component handling the player input and lander behaviour */
void LanderBehaviourComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects) {
	Component::Create(system, go, game_objects);
}

/* Update function for lander behaviour component */
void LanderBehaviourComponent::Update(float dt) {
	// Return if lander is inactive
	if (!m_go->m_enabled) { 
		return; 
	}

	Lander* lander = (Lander *)m_go;
	b2Body* body = lander->GetBody();

	// TODO: Better crash animation/sequence
	if (body == NULL) {
		lander->Crash();
		return;
	}

	b2Vec2 lander_pos = body->GetPosition();
	body->GetWorld()->RayCast(&raycast, lander_pos, b2Vec2(lander_pos.x, 0)); // Cast a ray from the position of the lander to the bottom of the level
	b2Vec2 ground_intersect = raycast.m_point;	
	lander->SetAltitude(lander_pos.y - ground_intersect.y);		// Calculate altitude (distance from lander to raycast intersection)

	if(body->GetLinearVelocity().LengthSquared() == 0) {		
		hover_time += dt;
		if (hover_time > WIN_TIME) {		// If the lander is completely still for a specified amount of time
			lander->Land();					// call the land method
		}
	} else {
		hover_time = 0;
	}

	AvancezLib::KeyStatus keys;				
	m_system->getKeyStatus(keys);
	lander->SetFiring(false);
	if (keys.fire) {
		lander->SetFiring(true);

		// Get the oposite direction of the lander
		float32 angle = body->GetAngle() + M_PI/2;
		b2Vec2 vec = b2Vec2(cos(angle), sin(angle));
		vec.Normalize();

		// Calculate force vector
		b2Vec2 force = b2Vec2(vec.x * LANDER_THRUST * dt, vec.y * LANDER_THRUST * dt);

		// Apply the specified amount of force in the right direction
		body->ApplyForceToCenter(force, true);
	}
	// Lander is rotated by setting the transform of the lander.
	if (keys.left && !keys.right) {
		b2Body* body = lander->GetBody();
		body->SetAngularVelocity(body->GetAngularVelocity() * 0.9f); // Reduce current angular velocity
		body->SetTransform(body->GetPosition(), body->GetAngle() + (LANDER_ROTATION_SPEED * dt));
	}
	if (keys.right && !keys.left) {
		b2Body* body = lander->GetBody();
		body->SetAngularVelocity(body->GetAngularVelocity() * 0.9f);
		body->SetTransform(body->GetPosition(), body->GetAngle() - (LANDER_ROTATION_SPEED * dt));
	}
}

void LanderRenderComponent::Create(AvancezLib* system, Lander* go, std::set<GameObject*>* game_objects, const char* lander_sprite, const char** sprites, int num_sprites) {
	Component::Create(system, go, game_objects);

	this->num_sprites = num_sprites;
	m_sprites = new Sprite* [num_sprites];

	m_default_sprite = system->createSprite(lander_sprite);
	for (int i = 0; i < num_sprites; i++) {
		m_sprites[i] = system->createSprite(sprites[i]);
	}
}

void LanderRenderComponent::Update(float dt) {

	if (!m_go->m_enabled) {
		return;
	}
	if (((Lander *)m_go)->IsFiring()) {
		m_sprites[animation]->draw(int(m_go->m_horizontalPosition), int(m_go->m_verticalPosition), m_go->m_angle);
		animation = (animation + 1) % num_sprites;
	} else {
		m_default_sprite->draw(int(m_go->m_horizontalPosition), int(m_go->m_verticalPosition), m_go->m_angle);
	}

}


#include "lunarlander.h"

void LunarLander::Create(AvancezLib* system, FMOD::Studio::System* fmod_studio) {

	Game::Create(system, fmod_studio);

	InitWorld();
	InitLander();	
	
	world->ClearForces();
}

void LunarLander::Update(float dt) {
	if (IsGameOver())
		dt = 0.f;

	world->Step(PHYSICS_TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	world->DrawDebugData();
	fmod_studio->update();

	for (auto go : game_objects)
		go->Update(dt);

	for (b2Joint* j : joints_tbd) {
		world->DestroyJoint(j);
	}
	joints_tbd.clear();
	for (b2Body* b : bodies_tbd) {
		world->DestroyBody(b);
	}
	bodies_tbd.clear();
}

void LunarLander::Draw() {
	float angle = lander_core->GetAngle();
	float x = cos(angle);
	float y = sin(angle);
	b2Vec2 vel = lander_core->GetLinearVelocity();
	char msg[1024];
	sprintf(msg, "Score: %d", score);
	system->drawText(100, 32, msg);
	sprintf(msg, "Angle: %d", (int)(angle * 180.0f / 3.14f));
	system->drawText(300, 32, msg);
	sprintf(msg, "Horizontal speed: %d", (int)vel.x);
	system->drawText(400, 32, msg);
	sprintf(msg, "Vertical speed: %d", (int)vel.y);
	system->drawText(400, 64, msg);


	if (IsGameOver())
	{
		sprintf(msg, "*** G A M E  O V E R ***");
		system->drawText(250, 8, msg);
	}
}

void LunarLander::Destroy() {
	Game::Destroy();
	delete world;
}

void LunarLander::Receive(Message m) {
	switch (m)
	{
	case CRASH:
		score += 10;
		//Restart();
		break;
	case LAND:
		score += 100;
		//Restart();
		break;
	default:
		break;
	}
}

// Initialize Box2D world
void LunarLander::InitWorld() { 
	
	b2Vec2 gravity(0.0f, -0.25f);
	world = new b2World(gravity);

	collision = CollisionCallback();
	collision.Init(&bodies_tbd, &joints_tbd);
	world->SetContactListener(&collision);

	b2BodyDef groundDef;
	groundDef.position.Set(320.0f, 16.0f);
	groundDef.type = b2_staticBody;

	groundBody = world->CreateBody(&groundDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(320.0f, 16.0f);

	b2FixtureDef groundFixture;
	groundFixture.shape = &groundShape;
	groundFixture.friction = 1.0f;

	groundBody->CreateFixture(&groundFixture);

	ground = new Ground();

	RenderComponent* render = new RenderComponent();
	render->Create(system, ground, &game_objects, "data/ground_box.bmp");

	PhysicsComponent* physics = new PhysicsComponent();
	physics->Create(system, ground, &game_objects, groundBody);

	b2Vec2 groundSize = b2Vec2(640.0f, 32.0f);

	ground->Create(groundSize, groundBody);
	ground->AddComponent(render);
	ground->AddComponent(physics);
	game_objects.insert(ground);
	
}

// Initializes the Lander game objects and b2Bodies
void LunarLander::InitLander() { 

	lander = new Lander();	// Construct lander game object

	// Create lander body
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(LANDER_START_X, LANDER_START_Y);
		lander_core = world->CreateBody(&bd);

		b2PolygonShape shape;
		shape.SetAsBox(LANDER_HALF_WIDTH, LANDER_HALF_HEIGHT);
		lander_core->CreateFixture(&shape, LANDER_DENSITY);

		lander_core->SetUserData((void*)1);
	}

	std::set<b2Body*> lander_legs;

	// Add left leg
	{
		b2PolygonShape shape;
		shape.SetAsBox(4.0f, 1.0f);

		b2Body* left_leg = NULL;
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(LANDER_START_X-(LANDER_HALF_WIDTH + 4.0f), LANDER_START_Y-LANDER_HALF_HEIGHT);
		left_leg = world->CreateBody(&bd);
		left_leg->CreateFixture(&shape, LANDER_DENSITY);
		left_leg->SetUserData((void*)2);

		lander_legs.insert(left_leg);

		b2RevoluteJointDef rjd;
		rjd.Initialize(lander_core, left_leg, b2Vec2(LANDER_START_X-LANDER_HALF_WIDTH, LANDER_START_Y-LANDER_HALF_HEIGHT));
		rjd.referenceAngle = 30 * DEGTORAD;
		rjd.enableLimit = true;
		rjd.lowerAngle = -2 * DEGTORAD;
		rjd.upperAngle = 2 * DEGTORAD;
		world->CreateJoint(&rjd);

		b2Body* left_leg_end = NULL;
		b2BodyDef bd2;
		bd2.type = b2_dynamicBody;
		bd2.position.Set(LANDER_START_X -(LANDER_HALF_WIDTH + 4.0f * 3), LANDER_START_Y-LANDER_HALF_HEIGHT);
		left_leg_end = world->CreateBody(&bd2);
		left_leg_end->CreateFixture(&shape, LANDER_DENSITY);
		left_leg_end->SetUserData((void*)2);

		lander_legs.insert(left_leg_end);

		b2RevoluteJointDef rjd2;
		rjd2.Initialize(left_leg, left_leg_end, b2Vec2(LANDER_START_X -(LANDER_HALF_WIDTH + 4.0f * 2), LANDER_START_Y-LANDER_HALF_HEIGHT));
		rjd2.referenceAngle = 30 * DEGTORAD;
		rjd2.enableLimit = true;
		rjd2.lowerAngle = -2 * DEGTORAD;
		rjd2.upperAngle = 2 * DEGTORAD;
		world->CreateJoint(&rjd2);

	}


	// Add right leg
	{
		b2PolygonShape shape;
		shape.SetAsBox(4.0f, 1.0f);

		b2Body* right_leg = NULL;
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(LANDER_START_X + LANDER_HALF_WIDTH + 4.0f , LANDER_START_Y -LANDER_HALF_HEIGHT);
		right_leg = world->CreateBody(&bd);
		right_leg->CreateFixture(&shape, LANDER_DENSITY);
		right_leg->SetUserData((void*)2);

		lander_legs.insert(right_leg);

		b2RevoluteJointDef rjd;
		rjd.Initialize(lander_core, right_leg, b2Vec2(LANDER_START_X + LANDER_HALF_WIDTH, LANDER_START_Y -LANDER_HALF_HEIGHT));
		rjd.referenceAngle = -30 * DEGTORAD;
		rjd.enableLimit = true;
		rjd.lowerAngle = 2 * DEGTORAD;
		rjd.upperAngle = -2 * DEGTORAD;
		world->CreateJoint(&rjd);

		b2Body* right_leg_end = NULL;
		b2BodyDef bd2;
		bd2.type = b2_dynamicBody;
		bd2.position.Set(LANDER_START_X + LANDER_HALF_WIDTH + 4.0f * 3, LANDER_START_Y -LANDER_HALF_HEIGHT);
		right_leg_end = world->CreateBody(&bd2);
		right_leg_end->CreateFixture(&shape, LANDER_DENSITY);
		right_leg_end->SetUserData((void*)2);

		lander_legs.insert(right_leg_end);

		b2RevoluteJointDef rjd2;
		rjd2.Initialize(right_leg, right_leg_end, b2Vec2(LANDER_START_X + LANDER_HALF_WIDTH + 4.0f * 2, LANDER_START_Y-LANDER_HALF_HEIGHT));
		//rjd2.collideConnected = true;
		rjd2.referenceAngle = -30 * DEGTORAD;
		rjd2.enableLimit = true;
		rjd2.lowerAngle = 2 * DEGTORAD;
		rjd2.upperAngle = -2 * DEGTORAD;
		world->CreateJoint(&rjd2);
	}

	for (b2Body* b : lander_legs) {
		GameObject* go = new GameObject();

		PhysicsComponent* physics = new PhysicsComponent();
		physics->Create(system, go, &game_objects, b);

		RenderComponent* render = new RenderComponent();
		render->Create(system, go, &game_objects, "data/leg_ph.bmp");

		go->Create(b2Vec2(8.0f, 2.0f));
		go->AddComponent(physics);
		go->AddComponent(render);
		game_objects.insert(go);
	}

	/* Create lander components */
	PhysicsComponent* physics = new PhysicsComponent();
	physics->Create(system, lander, &game_objects, lander_core);

	LanderBehaviourComponent* behaviour = new LanderBehaviourComponent();
	behaviour->Create(system, lander, &game_objects);

	std::set<const char*>* sprites;
	sprites = new std::set<const char*>();
	sprites->insert("data/Lander_firing.bmp");

	LanderRenderComponent* render = new LanderRenderComponent();
	render->Create(system, lander, &game_objects, "data/PH-lander.bmp", sprites);

	b2Vec2 size = b2Vec2(LANDER_HALF_WIDTH * 2, LANDER_HALF_HEIGHT * 2);

	lander->Create(size, lander_core);
	lander->AddComponent(physics);
	lander->AddComponent(behaviour);
	lander->AddComponent(render);
	lander->AddReceiver(this);
	game_objects.insert(lander);


}


#include "lunarlander.h"

void LunarLander::Create(AvancezLib* system, FMOD::Studio::System* fmod_studio) {

	Game::Create(system, fmod_studio);

	InitWorld();
	InitLander();	
	

}

void LunarLander::Update(float dt) {
	if (IsGameOver())
		dt = 0.f;

	world->Step(PHYSICS_TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	fmod_studio->update();

	for (auto go : game_objects)
		go->Update(dt);
}

void LunarLander::Draw() {
	float angle = landerBody->GetAngle();
	float x = cos(angle);
	float y = sin(angle);
	b2Vec2 vel = landerBody->GetLinearVelocity();
	char msg[1024];
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

// Initialize Box2D world
void LunarLander::InitWorld() { 
	
	b2Vec2 gravity(0.0f, -0.25f);
	world = new b2World(gravity);

	collision = CollisionCallback();

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

// Initializes the Lander game object and b2Body
void LunarLander::InitLander() { 

	lander = new Lander();	// Construct lander game object

	/* Construct lander bodydef, shape, fixture and body */
	b2BodyDef bodyDef;
	bodyDef.position.Set(LANDER_START_X, LANDER_START_Y);
	bodyDef.type = b2_dynamicBody;

	landerBody = world->CreateBody(&bodyDef);

	landerBody->SetUserData(lander);

	b2PolygonShape shape;
	shape.SetAsBox(LANDER_WIDTH / 2.0f, LANDER_HEIGHT / 2.0f);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = LANDER_DENSITY;
	fixture.friction = LANDER_FRICTION;

	landerBody->CreateFixture(&fixture);

	/* Create lander components */
	PhysicsComponent* physics = new PhysicsComponent();
	physics->Create(system, lander, &game_objects, landerBody);

	LanderBehaviourComponent* behaviour = new LanderBehaviourComponent();
	behaviour->Create(system, lander, &game_objects);

	RenderComponent* render = new RenderComponent();
	render->Create(system, lander, &game_objects, "data/PH-lander.bmp");

	b2Vec2 size = b2Vec2(LANDER_WIDTH, LANDER_HEIGHT);

	lander->Create(size, landerBody);
	lander->AddComponent(physics);
	lander->AddComponent(behaviour);
	lander->AddComponent(render);
	lander->AddReceiver(this);
	game_objects.insert(lander);


}


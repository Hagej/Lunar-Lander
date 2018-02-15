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

	b2BodyDef groundDef;
	groundDef.position.Set(0.0f, 32.0f);
	groundDef.type = b2_staticBody;

	b2Body* ground;
	ground = world->CreateBody(&groundDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(200.0f, 10.0f);

	b2FixtureDef groundFixture;
	groundFixture.shape = &groundShape;
	groundFixture.friction = 1.0f;

	ground->CreateFixture(&groundFixture);
}

// Initializes the Lander game object and b2Body
void LunarLander::InitLander() { 

	lander = new Lander();	// Construct lander game object

	/* Construct lander bodydef, shape, fixture and body */
	b2BodyDef bodyDef;
	bodyDef.position.Set(LANDER_START_X, LANDER_START_Y);
	bodyDef.type = b2_dynamicBody;

	landerBody = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(LANDER_WIDTH / 2.0f, LANDER_HEIGHT / 2.0f);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = LANDER_DENSITY;
	fixture.friction = LANDER_FRICTION;

	landerBody->CreateFixture(&fixture);

	/* Create lander components */
	LanderPhysicsComponent* physics = new LanderPhysicsComponent();
	physics->Create(system, lander, &game_objects, landerBody);

	LanderBehaviourComponent* behaviour = new LanderBehaviourComponent();
	behaviour->Create(system, lander, &game_objects, landerBody);

	RenderComponent* render = new RenderComponent();
	render->Create(system, lander, &game_objects, "data/PH-lander.bmp");

	lander->Create();
	lander->AddComponent(physics);
	lander->AddComponent(behaviour);
	lander->AddComponent(render);
	lander->AddReceiver(this);
	lander->m_horizontalPosition = LANDER_START_X;
	lander->m_verticalPosition = LANDER_START_Y;
	game_objects.insert(lander);


}


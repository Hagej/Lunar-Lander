#include "lunarlander.h"

/* Constructor for the game Lunar Lander */
void LunarLander::Create(AvancezLib* system, FMOD::Studio::System* fmod_studio) {

	Game::Create(system, fmod_studio);

	InitWorld();
	level_handler.Create(world, &bodies_tbd, &joints_tbd);
	level_handler.GenerateLevel(1920, 500);
	
	LevelComponent* levelComponent = new LevelComponent();
	levelComponent->Create(system, &level_handler, &game_objects, camera);
	level_handler.AddComponent(levelComponent);

	game_objects.insert(&level_handler);
	InitLander();	
}

/* The game loop. Updates the Box2D world, FMOD Studio and all the game objects. Clears the world of objects that are removed. */
void LunarLander::Update(float dt) {
	if (IsGameOver())
		dt = 0.f;
	
	if (restart) {
		restart = false;
		Restart();
		return;
	}

	world->Step(PHYSICS_TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	fmod_studio->update();

	for (auto go : game_objects) {
		go->Update(dt);
	}

	for (b2Joint* j : joints_tbd) {
		world->DestroyJoint(j);
	}
	joints_tbd.clear();
	for (b2Body* b : bodies_tbd) {
		if (b == lander->GetBody()) {
			lander->Crash();
		}
		world->DestroyBody(b);
	}
	bodies_tbd.clear();

}

/* Method that draws the ui of the game */
void LunarLander::Draw() {
	char msg[1024];
	sprintf(msg, "Score: %d", score);
	system->drawText(100, 32, msg);
	if (lander->m_enabled) {
		float angle = lander->GetBody()->GetAngle();
		float x = cos(angle);
		float y = sin(angle);
		b2Vec2 vel = lander->GetBody()->GetLinearVelocity();
		sprintf(msg, "Fuel: %d", (int)lander->GetFuel());
		system->drawText(100, 64, msg);
		sprintf(msg, "Angle: %d", (int)(angle * 180.0f / 3.14f));
		system->drawText(500, 32, msg);
		sprintf(msg, "Altitude: %d", (int)(lander->GetAltitude()));
		system->drawText(500, 64, msg);
		sprintf(msg, "Horizontal speed: %d", (int)vel.x);
		system->drawText(650, 32, msg);
		sprintf(msg, "Vertical speed: %d", (int)vel.y);
		system->drawText(650, 64, msg);
	} else {
		sprintf(msg, "Angle: 0");
		system->drawText(500, 32, msg);
		sprintf(msg, "Altitude: 0");
		system->drawText(500, 64, msg);
		sprintf(msg, "Horizontal speed: 0");
		system->drawText(650, 32, msg);
		sprintf(msg, "Vertical speed: 0");
		system->drawText(650, 64, msg);
	}


	if (IsGameOver())
	{
		sprintf(msg, "*** G A M E  O V E R ***");
		system->drawText(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 100, msg);
	}
}

/* Destroys the game instance and the Box2D world. */
void LunarLander::Destroy() {
	Game::Destroy();
	delete world;
}

/* Handles main game messages */
void LunarLander::Receive(Message m) {
	int parts_left;

	switch (m)
	{
	case CRASH:	// If the player crashes points are increased slightly and the next level starts
		score += 10;
		fuel_left = 0; 
		restart = true;
		break;
	case LAND:	// If the player lands points are increased depending on the amount of parts left on the lander. The next level starts
		parts_left = lander->AttachedBodies();
		LOG("Parts left: %d", parts_left);
		score += 20 * parts_left;
		fuel_left = 100;
		restart = true;
		break;
	case GAME_OVER:
		game_over = true;
	default:
		break;
	}
}

/* Restarts the game */
void LunarLander::Restart() {
	fuel_left += lander->GetFuel();
	for (auto go : game_objects) // Destroy all game objects
		go->Destroy();
	game_objects.clear();

	level_handler.ClearWorld();
	level_handler.GenerateLevel(1920, 500);

	LevelComponent* levelComponent = new LevelComponent();
	levelComponent->Create(system, &level_handler, &game_objects, camera);
	level_handler.AddComponent(levelComponent);

	game_objects.insert(&level_handler);

	camera->SetPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera->SetZoom(0.5f);
	
	InitLander();
	lander->SetFuel(fuel_left);
	for (auto go : game_objects)
		go->Init();

}

/* Initializes the lander game object and adds its components */
void LunarLander::InitLander() {

	lander = new Lander();
	lander->Create(b2Vec2(40.0f, 40.0f), world);

	/* Create lander components */
	PhysicsComponent* physics = new PhysicsComponent();
	physics->Create(system, lander, &game_objects, lander->GetBody());

	LanderBehaviourComponent* behaviour = new LanderBehaviourComponent();
	behaviour->Create(system, lander, &game_objects);

	RenderComponent* render = new RenderComponent();
	render->Create(system, lander, &game_objects, camera, "data/lander.bmp");

	ParticleComponent* particles = new ParticleComponent();
	particles->Create(system, lander, &game_objects, world, &bodies_tbd, camera);

	CameraBehaviourComponent* cameraBehaviour = new CameraBehaviourComponent();
	cameraBehaviour->Create(system, lander, &game_objects, camera);

	lander->AddComponent(physics);
	lander->AddComponent(behaviour);
	lander->AddComponent(render);
	lander->AddComponent(particles);
	lander->AddComponent(cameraBehaviour);
	lander->AddReceiver(this);
	game_objects.insert(lander);


	/* Initialize lander legs game objects and add components */
	for (b2Body* b : lander->GetLegs()) {
		GameObject* go = new GameObject();

		PhysicsComponent* physics = new PhysicsComponent();
		physics->Create(system, go, &game_objects, b);

		RenderComponent* render = new RenderComponent();
		render->Create(system, go, &game_objects, camera, "data/leg_ph.bmp");

		go->Create(b2Vec2(8.0f, 2.0f));
		go->AddComponent(physics);
		go->AddComponent(render);
		game_objects.insert(go);
	}

}

void LunarLander::InitWorld() {

	b2Vec2 gravity(0.0f, GRAVITY_CONSTANT);
	world = new b2World(gravity);

	collision = CollisionCallback();
	collision.Init(&bodies_tbd, &joints_tbd);
	world->SetContactListener(&collision);
}
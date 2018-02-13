

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;
	b2World * world;
	b2Body * landerBody;

	GameObject* lander;

	bool game_over;

	unsigned int score = 0;

public:

	virtual void Create(AvancezLib* system)
	{
		SDL_Log("Game::Create");

		this->system = system;

		// initialize physics system
		b2Vec2 gravity(0.0f, -0.25f);
		world = new b2World(gravity);

		initLander();	// initializes the lander game object and body



		score = 0;
	}

	virtual void Init()
	{
		for (auto go : game_objects)
			go->Init();

		m_enabled = true;
		game_over = false;
	}

	virtual void Update(float dt)
	{
		if (IsGameOver())
			dt = 0.f;

		world->Step(PHYSICS_TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		for (auto go : game_objects)
			go->Update(dt);
	}

	virtual void Draw()
	{
		char msg[1024];
		sprintf(msg, "physics demo");
		system->drawText(300, 32, msg);

		if (IsGameOver())
		{
			sprintf(msg, "*** G A M E  O V E R ***");
			system->drawText(250, 8, msg);
		}
	}

	virtual void Receive(Message m)
	{
		if (m == GAME_OVER)
			game_over = true;
	}

	bool IsGameOver()
	{
		return game_over;
	}

	unsigned int getScore()
	{
		return score;
	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go : game_objects)
			go->Destroy();

		delete world;
	}

private:

	void initLander() {

		LanderPhysicsComponent physics;
		physics.Create(system, lander, &game_objects, landerBody);
		
		lander->Create();
		lander->AddComponent(&physics);
		lander->AddReceiver(this);
		lander->m_horizontalPosition = LANDER_START_X;
		lander->m_verticalPosition = LANDER_START_Y;
		game_objects.insert(lander);

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

	}
};
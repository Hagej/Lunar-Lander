

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;
	b2World * world;
	b2Body * landerBody;

	Lander* lander;

	bool game_over;

	unsigned int score = 0;

public:

	virtual void Create(AvancezLib* system)
	{
#if LOG
		SDL_Log("Game::Create");
#endif

		this->system = system;

		// initialize physics system
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
		
		// TODO: Create ground objects
		/* CollideComponent* collision = new CollideComponent();
		collision->Create(system, lander, &game_objects, &ground_objects); */
		
		// TODO: Add .bmp of lander
		RenderComponent* render = new RenderComponent();
		render->Create(system, lander, &game_objects, "data/PH-lander.bmp");

		lander->Create();
		lander->AddComponent(physics);
		lander->AddComponent(behaviour);
		//lander->AddComponent(collision);
		lander->AddComponent(render);
		lander->AddReceiver(this);
		lander->m_horizontalPosition = LANDER_START_X;
		lander->m_verticalPosition = LANDER_START_Y;
		game_objects.insert(lander);


	}
};
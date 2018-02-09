

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;

	b2World * world;


	Box * static_box;
	Box * dynamic_box;

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

		// initialize static box here
		static_box = new Box();

		RenderComponent * static_render = new RenderComponent();
		static_render->Create(system, static_box, &game_objects, "data/box.bmp");

		BoxPhysicsComponent * static_component = new BoxPhysicsComponent();
		static_component->Create(system, world, static_box, &game_objects, b2_staticBody, 130, 192, 64, 64);
		
		static_box->Create();
		static_box->AddComponent(static_render);
		static_box->AddComponent(static_component);
		static_box->AddReceiver(this);
		game_objects.insert(static_box);

		// initialize dynamic box here
		dynamic_box = new Box();

		RenderComponent * dynamic_render = new RenderComponent();
		dynamic_render->Create(system, dynamic_box, &game_objects, "data/small_box.bmp");

		BoxPhysicsComponent * dynamic_component = new BoxPhysicsComponent;
		dynamic_component->Create(system, world, dynamic_box, &game_objects, b2_dynamicBody, 170, 400, 32, 32);

		dynamic_box->Create();
		dynamic_box->AddComponent(dynamic_render);
		dynamic_box->AddComponent(dynamic_component);
		dynamic_box->AddReceiver(this);
		game_objects.insert(dynamic_box);

		score = 0;
	}

	virtual void Init()
	{
		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Init();

		enabled = true;
		game_over = false;
	}

	virtual void Update(float dt)
	{
		if (IsGameOver())
			dt = 0.f;

		// update the physics module here

		world->Step(PHYSICS_TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Update(dt);
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

	unsigned int Score()
	{
		return score;
	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();

		delete static_box;
		delete dynamic_box;
		delete world;
	}
};
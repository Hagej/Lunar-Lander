
class BoxPhysicsComponent : public Component
{
	b2World* world;
	b2Body* body;

	float size_x, size_y;

public:

	virtual void Create(AvancezLib* system, b2World* world, GameObject * go, std::set<GameObject*> * game_objects, b2BodyType type, float pos_x, float pos_y, float size_x, float size_y)
	{
		Component::Create(system, go, game_objects);

		this->world = world;
		this->size_x = size_x / 2.f;
		this->size_y = size_y / 2.f;

		// define the physics object here

		b2BodyDef bodyDef;
		bodyDef.type = type;
		bodyDef.position.Set(pos_x, pos_y);
		body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(this->size_x, this->size_y);

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.3f;

		body->CreateFixture(&fixture);
	}

	virtual void Update(float dt)
	{
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		// update the state of the game object here
		go->horizontalPosition = position.x - size_x;
		go->verticalPosition = WINDOW_HEIGHT - (position.y + size_y);
		go->angle = angle * (-180 / 3.14f);
		
		if (position.y < 0) {
			go->enabled = false;
		}

	}

	virtual ~BoxPhysicsComponent()
	{
		world->DestroyBody(body);
	}
};



class Box : public GameObject
{
	BoxPhysicsComponent * physics;

public:

	virtual ~Box() { SDL_Log("Box::~Box"); }
};

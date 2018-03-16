#include "level_handler.h"
#include "game_defs.h"

#include <time.h>
#include <math.h>

void LevelHandler::Create(b2World* world, std::set<b2Body*>* bodies_tbd, std::set<b2Joint*>* joints_tbd) {
	LOG("LevelHandler::Create");
	GameObject::Create(b2Vec2(0, 0));

	m_world = world;

	groundFixtureDef.friction = 1.0f;
	groundFixtureDef.filter.categoryBits = 0x0004;

}

void LevelHandler::GenerateLevel(const int width, const int height) {
	
	srand(time(NULL));
	groundDef.type = b2_staticBody;
	groundDef.userData = (void*)GROUND;
	cur_level = m_world->CreateBody(&groundDef);

	int x = 0;
	int slope = 1;
	int dx, dy;
	int last_height = rand() % height + MIN_HEIGHT;
	int next_goal = rand() % 100 + 300;
	int slope_width = rand() % 600 + 300;
	while (x <= width) {

		if (next_goal < 0) {
			next_goal = rand() % 100 + 300;
			dx = rand() % (GOAL_MAX_WIDTH - GOAL_MIN_WIDTH) + GOAL_MIN_WIDTH;
			dy = 0;
		}
		else {
			dx = rand() % (SLICE_MAX_WIDTH - SLICE_MIN_WIDTH) + SLICE_MIN_WIDTH;
			dy = rand() % (SLICE_MAX_HEIGHT - SLICE_MIN_HEIGHT) + SLICE_MIN_HEIGHT;
			if (slope_width < 0 || last_height + (slope * dy) > height || last_height + (slope * dy) < MIN_HEIGHT) {
				slope_width = rand() % 600 + 300;
				slope *= -1;
			}
		}

		b2Vec2 verts[4];
		verts[0] = b2Vec2(x, last_height);
		verts[1] = b2Vec2(x + dx, last_height + (slope * dy));
		verts[2] = b2Vec2(x + dx, 0);
		verts[3] = b2Vec2(x, 0);

		b2PolygonShape* shape = new b2PolygonShape();
		shape->Set(verts, 4);
		
		groundFixtureDef.shape = shape;
		cur_level->CreateFixture(&groundFixtureDef);
		
		x += dx;
		slope_width -= dx;
		next_goal -= dx;
		last_height += (slope*dy);

	}
}

void LevelHandler::ClearWorld() {

	b2Body* b = m_world->GetBodyList();
	b2Body* next;
	while (b != NULL) {			// Destroy all Box2D bodies
		next = b->GetNext();
		m_world->DestroyBody(b);
		b = next;
	}
}

void LevelComponent::Create(AvancezLib* system, LevelHandler* go, std::set<GameObject*>* game_objects, Camera* camera) {
	Component::Create(system, go, game_objects);

	m_camera = camera;
	m_level = go->GetLevel();

	sprite = system->createSprite("data/ground_slice.bmp");


}

void LevelComponent::Update(float dt) {

	b2Fixture* fixture = m_level->GetFixtureList();
	while (fixture) {
		
		b2PolygonShape* shape = (b2PolygonShape *)fixture->GetShape();
		b2EdgeShape* edge = new b2EdgeShape();
		edge->Set(shape->m_vertices[2], shape->m_vertices[1]);

		b2Vec2 vert1 = edge->m_vertex1;
		b2Vec2 vert2 = edge->m_vertex2;


		float zoom = m_camera->GetZoom();
		
		float32 width = vert2.x - vert1.x;
		float32 height = abs(vert1.y - vert2.y);

		float32 length = sqrt(pow(width, 2) + pow(height, 2)) * zoom;

		//SDL_Log("Data: %f, %f, %f", width, height, length);

		float32 center_x = vert2.x - (width/2.f);
		float32 center_y = std::max(vert1.y, vert2.y) - (height/2.f);
		m_camera->WorldToScreen(&center_x, &center_y);

		//SDL_Log("Center: %f, %f", center_x, center_y);

		float angle = atan((vert2.y - vert1.y) / abs(vert2.x - vert1.x)) * -RADTODEG; 

		sprite->draw(center_x - (length/2), center_y , angle, length, 1);
		//SDL_Log("y-value %f, %f",center_y - (height*zoom) / 2, center_y + (height*zoom)/2);
		fixture = fixture->GetNext();
	}


}


#include <iostream>
#include "defines.h"	// Contains all constants used

#include "Box2D/Box2D.h"
#include "avancezlib.h"

#include "object_pool.h"
#include "component.h"
#include "game_object.h"

#include "lander.h"
#include "game.h"

using namespace std;

float game_speed = 1.f;

int main(int argc, char** argv)
{
	AvancezLib system;

	system.init(WINDOW_WIDTH, WINDOW_HEIGHT);

	Game game;
	game.Create(&system);
	game.Init();

	float lastTime = system.getElapsedTime();
	while (system.update())
	{
		float newTime = system.getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * game_speed;
		lastTime = newTime;

		game.Update(dt);

		game.Draw();
	}

	// clean up
	game.Destroy();
	system.destroy();

	return 0;
}
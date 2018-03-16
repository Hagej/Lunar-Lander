#include <iostream>
#include "system_defs.h"	// Contains all constants used

#include "fmod.hpp"			// Low level library for Fmod
#include "fmod_studio.hpp"	// Fmod studio which manages sound banks
#include "fmod_errors.h"	// Error logging for Fmod

#include "avancezlib.h"

#include "lunarlander.h"

using namespace std;

/* Variable for modifying game speed. Not used in Lunar Lander */
float game_speed = 1.f;

/* Method for checking FMOD errors */
void fmodErrCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		printf("fmod error: %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	AvancezLib system;
	system.init(WINDOW_WIDTH, WINDOW_HEIGHT);

	FMOD::System* fmod_low_level = NULL;
	FMOD::Studio::System* fmod_studio = NULL;

	fmodErrCheck( FMOD::Studio::System::create(&fmod_studio) );
	fmodErrCheck( fmod_studio->getLowLevelSystem(&fmod_low_level) );
	fmodErrCheck( fmod_low_level->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0) );

	fmodErrCheck( fmod_studio->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0) );

	// Init the game object. Set type to the game that is being played
	LunarLander game;
	game.Create(&system, fmod_studio);
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

		fmod_studio->update();
	}

	// clean up
	game.Destroy();
	system.destroy();

	return 0;
}
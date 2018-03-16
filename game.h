#pragma once

/* Header file for games. Include this when creating a new game */

#include <iostream>
#include "game_defs.h"	// Contains all constants used within the game

#include "fmod.hpp"			// Low level library for Fmod
#include "fmod_studio.hpp"	// Fmod studio which manages sound banks
#include "fmod_errors.h"	// Error logging for Fmod

#include "avancezlib.h"

#include "object_pool.h"
#include "component.h"
#include "game_object.h"


class Game : public GameObject
{
protected:

	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;
	FMOD::Studio::System* fmod_studio;
	Camera* camera;

	unsigned int score = 0;

	bool game_over;



public:

	/* Inits the main system, sound system and the main camera of the game */
	virtual void Create(AvancezLib* system, FMOD::Studio::System* fmod_studio) {	
		LOG("Game::Create");
		this->system = system;
		this->fmod_studio = fmod_studio;
		camera = new Camera(960, 540, 960, 540);
		score = 0;
	}

	/* Enables all game objects in the game */
	virtual void Init() {
		for (auto go : game_objects)
			go->Init();

		//m_enabled = true;		Redundant? 
		game_over = false;
	}

	/* Default update function of the game class */
	virtual void Update(float dt)
	{
		if (IsGameOver())
			dt = 0.f;

		fmod_studio->update();

		for (auto go : game_objects)
			go->Update(dt);
	}

	/* Default method for drawing the UI of the game */
	virtual void Draw() {}

	/* Default recieve method of the game. Handles game altering messages such as GAME_OVER */
	virtual void Receive(Message m) {
		if (m == GAME_OVER)
			game_over = true;
	}

	bool IsGameOver() { return game_over; }

	unsigned int getScore() { return score; }

	/* Default destroy method. Destroys all game objects and the sound system */
	virtual void Destroy() {
		LOG("Game::Destroy");
		for (auto go : game_objects)
			go->Destroy();

		fmod_studio->release();
	}
	
};
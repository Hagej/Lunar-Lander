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

	unsigned int score = 0;

	bool game_over;



public:

	virtual void Create(AvancezLib* system, FMOD::Studio::System* fmod_studio) {	// Inits the system and sound
#if LOG
		SDL_Log("Game::Create");
#endif
		this->system = system;
		this->fmod_studio = fmod_studio;
		score = 0;

	}

	virtual void Init() {
		for (auto go : game_objects)
			go->Init();

		m_enabled = true;
		game_over = false;
	}

	virtual void Update(float dt)
	{
		if (IsGameOver())
			dt = 0.f;

		fmod_studio->update();

		for (auto go : game_objects)
			go->Update(dt);
	}

	virtual void Draw() {}

	virtual void Receive(Message m) {
		if (m == GAME_OVER)
			game_over = true;
	}

	bool IsGameOver() { return game_over; }

	unsigned int getScore() { return score; }

	virtual void Destroy() {
#if LOG
		SDL_Log("Game::Destroy");
#endif

		for (auto go : game_objects)
			go->Destroy();

		fmod_studio->release();
	}
	
};
#pragma once
#ifndef _SDLGAME_H_
#define _SDLGAME_H_

#include <SDL.h>
#include "SDL_Console\DT_Drawtext.h"
#include "SDL_Console\SDL_Console.h"
#include "SdlEvents.h"
#include "Scale2X.h"
#include "Entity.h"
#include "Tile.h"
#include "Player.h"
#include "Definitions.h"

class MegaDude : public SdlEvents
{
private:
	bool _gameRunning;
	ConsoleState _console;
	Surfaces _surfaces;
	GameState _gameState;
	GameKeysState _gameKeysState;
	Player* _player;
	Player* _testNpc;

public:
	MegaDude();
	int Execute();

private:
    bool Init();
    void HandleGameKeys();
	void Calculate();
    void Render();
	void DrawConsole();
    void Cleanup();	
	
	// GameEvents member implementations
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnExit();
};

#endif
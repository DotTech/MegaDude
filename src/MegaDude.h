#pragma once
#ifndef _SDLGAME_H_
#define _SDLGAME_H_

#include <SDL.h>
#include "MegaDude.h"
#include "SdlEvents.h"
#include "Sprite.h"

#define DATAFILE_TITLESCREEN "d:\\Data\\MegaDude\\src\\data\\titlescreen.bmp"
#define DATAFILE_SPRITESHEET "d:\\Data\\MegaDude\\src\\data\\sprites_megaman.bmp"
#define DATAFILE_CONSOLEFONT "d:\\Data\\MegaDude\\src\\data\\ConsoleFont.bmp"

class MegaDude : public SdlEvents
{
private:
	bool _running;
	int _lastTick;
	SDL_Surface* _displaySurface;
	SDL_Surface* _spriteSurface;
	SDL_Surface* _bgSurface;

public:
	MegaDude();
	int Execute();

private:
    bool Init();
    void HandleEvents(SDL_Event* sdlEvent);
    void Calculate();
    void Render();
    void Cleanup();
	
	// GameEvents member implementations
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnExit();
};

#endif
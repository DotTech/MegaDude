#pragma once
#ifndef _SDLGAME_H_
#define _SDLGAME_H_

#include <SDL.h>
#include "SdlEvents.h"
#include "Sprite.h"
#include "Definitions.h"

class MegaDude : public SdlEvents
{
private:
	bool _running;
	SDL_Surface* _displaySurface;
	SDL_Surface* _spriteSurface;
	SDL_Surface* _bgSurface;
	Sprite* _player;

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
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnExit();
};

#endif
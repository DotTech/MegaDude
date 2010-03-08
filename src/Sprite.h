#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <vector>
#include <SDL.h>
#include "SpriteAnimation.h"
#include "Definitions.h"

class Sprite : public SpriteAnimation
{
public:
	static std::vector<Sprite*> SpriteList;	// List with all the loaded sprites
	int MovementRate;			// Ticks elapsed per movement
	Uint32 LastMovementTick;	// Ticks value at last movement
	int Width;					// Sprite width
	int Height;					// Sprite height
	int X;						// X location
	int Y;						// Y location

public:
	Sprite();
	static void Init();					// Initialize sprite data
	SDL_Rect DestRect();				// Destination rectangle, this already includes the necessary FrameOffsetX
	void SetSequence(int animation);	// Set another sprite animation sequence (eg SPRITES_MEGAMAN_WALK or SPRITES_MEGAMAN_JUMP)
};

#endif
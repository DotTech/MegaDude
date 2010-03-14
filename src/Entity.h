#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <vector>
#include <SDL.h>
#include "SpriteAnimation.h"
#include "Definitions.h"

class Entity
{
public:
	static std::vector<Entity*> EntityList;	// List with all the available entities
	SpriteAnimation* Animation; // Active animation for this entity
	int CurrentAnimation;		// Currently selected animation sequence (eg SPRITES_MEGAMAN_WALK or SPRITES_MEGAMAN_JUMP)
	int MovementRate;			// Ticks elapsed per movement
	Uint32 LastMovementTick;	// Ticks value at last movement
	int Width;					// Sprite width
	int Height;					// Sprite height
	int X;						// X location
	int Y;						// Y location
	bool Direction;				// Direction into the enity is facing (left=true, right=false)

public:
	Entity();
	static void Init();					// Initialize sprite data
	SDL_Rect FrameDestRect();			// Destination rectangle, this already includes the necessary FrameOffsetX
	void SetAnimation(int sequence, 
					  bool resetCurrentFrame);	// Set another sprite animation sequence (eg SPRITES_MEGAMAN_WALK or SPRITES_MEGAMAN_JUMP)
};

#endif
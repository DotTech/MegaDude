#pragma once
#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <vector>
#include <SDL.h>

#define SPRITES_FRAMERATE		100	// Default animation framerate
#define SPRITES_TRANSPARANCY_R	255	// Transparancy color R value
#define SPRITES_TRANSPARANCY_G	0	// Transparancy color G value
#define SPRITES_TRANSPARANCY_B	233	// Transparancy color B value
#define SPRITES_MEGAMAN_IDLE	1	// Megaman idle sprite
#define SPRITES_MEGAMAN_WALK	2	// Megaman walking sprite
#define SPRITES_MEGAMAN_JUMP	3	// Megaman jumping sprite

class Sprite
{
public:
	static std::vector<Sprite*> SpriteList;	// List with all the loaded game sprites
	
	std::vector<SDL_Rect*> Frames;	// Animation frames
	int CurrentFrame;	// Active animation frame
	int FrameRate;		// Ticks per frame
	bool Flipped;		// If true the sprite is vertically flipped
	int Width;			// Sprite width
	int Height;			// Sprite height
	int X;				// X location
	int Y;				// Y location


private:
	int FrameOffsetX();					// Frames dont always have the same width. This offset is the amount of pixels needed to put the frame in the center of the sprite.

public:
	Sprite();
	static void InitSprites();			// Initialize sprite data
	SDL_Rect DestRect();				// Destination rectangle, this already includes the necessary FrameOffsetX

};

#endif
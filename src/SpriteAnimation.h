#pragma once
#ifndef _SPRITEANIMATION_H_
#define _SPRITEANIMATION_H_

#include <vector>
#include <string>
#include <SDL.h>
#include "Definitions.h"

using namespace std;

class SpriteAnimation
{

private:
	int TotalFrames;		// Number of frames for this sprite. Note that the actual number is twice as much because each frame has a 2nd version that faces in the other direction
	void NextFrame();		// Set next animation frame as current frame
	int ReadAnimationIndex(string line);		// Extracts the index from an animation definition line
	int ReadLineValue(string line, string key);	// Read a key value from an animation definition line

protected:
	void InitAnimations();				// Initialize sprite animation data, called by Sprite::Init()
	int FrameOffsetX(int spriteWidth);	// Frames dont always have the same width. This offset is the amount of pixels needed to put the frame in the center of the sprite.

public:
	SpriteAnimation(void);
	vector<SpriteAnimation*> SpriteAnimationList;	// List with ALL the loaded sprite animations
	vector<SDL_Rect*> Frames;		// Animation frames
	int CurrentFrame;				// Active animation frame. To get the frame facing in the other direction, add TotalFrame to the CurrentFrame.
	int FrameRate;					// Ticks elapsed per frame
	bool Flipped;					// If true the sprite is horizontally flipped
	Uint32 LastAnimationTick;		// Ticks value at last animation
	int CurrentSequence;			// Currently selected animation sequence (eg SPRITES_MEGAMAN_WALK or SPRITES_MEGAMAN_JUMP)
	SDL_Rect GetCurrentFrame();		// Returns the currently active frame source rect
	void DoAnimation();				// Set the next animation frame as current frame if enough ticks have passed

};

#endif
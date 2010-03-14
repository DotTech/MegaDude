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
	static int ReadLineValue(string line, string key);	// Read a key value from an animation definition line

public:
	SpriteAnimation(void);
	static vector<SpriteAnimation*> SpriteAnimationList;	// List with ALL the loaded sprite animations
	static void InitAnimations();							// Initialize sprite animation data
	vector<SDL_Rect*> Frames;		// Animation frames
	int CurrentFrame;				// Active animation frame. To get the frame facing in the other direction, add TotalFrame to the CurrentFrame.
	int FrameRate;					// Ticks elapsed per frame
	bool Loop;						// Loop the animation
	bool Flipped;					// If true the sprite is horizontally flipped
	Uint32 LastAnimationTick;		// Ticks value at last animation
	SDL_Rect GetCurrentFrame();		// Returns the currently active frame source rect
	void DoAnimation();				// Set the next animation frame as current frame if enough ticks have passed
	int FrameOffsetX(int spriteWidth);	// Frames dont always have the same width. This offset is the amount of pixels needed to put the frame in the center of the sprite.
	int FrameOffsetY(int spriteHeight);	// Frames dont always have the same height. This offset is the amount of pixels needed to put the frame aligned to the bottom of the sprite.
};

#endif
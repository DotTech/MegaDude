//  MODULE NAME: SpriteAnimation.cpp
//      PROJECT: SDL-based 2D Platform Game
//       AUTHOR: Ruud van Falier
//               ruud.vanfalier@gmail.com
//         DATE: March 9, 2010
//  DESCRIPTION: Base class for sprite animation. 
//               Sprite class must inherit from this class.

#include <fstream>
#include "SpriteAnimation.h"

// Constructor
SpriteAnimation::SpriteAnimation(void)
{
	FrameRate = SPRITES_FRAMERATE;
	Flipped = true;
	CurrentSequence = 0;
	TotalFrames = 0;
	CurrentFrame = 0;
	LastAnimationTick = 0;
}

// Activate the next animation frame
void SpriteAnimation::NextFrame()
{
	if (CurrentFrame < TotalFrames - 1)
		CurrentFrame++;
	else
		CurrentFrame = 0;
}

// Returns the source rectangle for the currently active frame.
// Takes the Flipped property into account.
SDL_Rect SpriteAnimation::GetCurrentFrame()
{
	SDL_Rect frame;
	SpriteAnimation* animation = SpriteAnimationList[CurrentSequence];

	if (Flipped)
		frame = *animation->Frames[animation->CurrentFrame + animation->TotalFrames];
	else
		frame = *animation->Frames[animation->CurrentFrame];

	return frame;
}

// Frames dont always have the same width. 
// This offset is the amount of pixels needed to put the frame in the center of the sprite.
int SpriteAnimation::FrameOffsetX(int spriteWidth)
{
	int offset = 0;

	SpriteAnimation* animation = SpriteAnimationList[CurrentSequence];
	int frameWidth = animation->Frames[animation->CurrentFrame]->w;
	
	if (frameWidth <= spriteWidth - 2)
	{
		offset = spriteWidth - frameWidth;
		offset = offset / 2;
	}
	
	return offset;
}

// Set the next animation frame as currentframe if enough ticks have passed
void SpriteAnimation::DoAnimation()
{
	SpriteAnimation* animation = SpriteAnimationList[CurrentSequence];

	if (animation->LastAnimationTick == 0 || SDL_GetTicks() - animation->LastAnimationTick >= (unsigned int)animation->FrameRate)
	{
		animation->NextFrame();
		animation->LastAnimationTick = SDL_GetTicks();
	}
}

// Read a key value from an animation definition line
int SpriteAnimation::ReadLineValue(string line, string key)
{
	key += ":";

	// Find the key trailed by colon sign
	int startPos = line.find(key);
	if (startPos != string.npos)
	{
		startPos += key.length();
		line = line.substr(startPos, line.length() - startPos);

		// Find semicolon
		int scolonPos = line.find_first_of(";");

		// Return the found value
		return atoi(line.substr(0, scolonPos).c_str());
	}

	return -1;
}

// Load the spritesheets and initializes the sprite animations
void SpriteAnimation::InitAnimations()
{
	// We load the animation definitions from a text file.
	// Animations are defined like this:
	//
	// F:<frame_rate>						-- General properties
	// X:<x>;Y:<y>;W:<width>;H:<height>		-- Frame 1
	// X:<x>;Y:<y>;W:<width>;H:<height>		-- Frame 2
	// E:1;									-- End sequence

	// Load animation definition file into string vector
	vector<string> definition;
	ifstream file(DATAFILE_ANIMATIONSDEF);
	
	string line;
	while (getline(file, line))
	{
		definition.push_back(line);
	}

	// Loop through all file lines and create the animation objects
	SpriteAnimation* spriteAnimation;
	
	for (int i=0; i<(int)definition.size(); i++)
	{
		line = definition[i];

		// Skip comments and empty lines
		if (line.length() > 0 && line.substr(0, 2) != "//")
		{
			// If the F (framerate) key is found this is not a frame definition,
			// but the definition of a whole new animation sequence.
			// So we create a new animation object
			int frameRate = ReadLineValue(line, "F");
			int endSequence = ReadLineValue(line, "E");

			if (frameRate != -1)
			{
				// Start a new animation sequence
				spriteAnimation = new SpriteAnimation;
				spriteAnimation->FrameRate = frameRate;
			}
			else if (endSequence != -1)
			{
				// End current animation sequence.
				// But not before we added flipped versions of all frames.
				spriteAnimation->TotalFrames = spriteAnimation->Frames.size();

				for (int i=0; i<spriteAnimation->TotalFrames; i++)
				{
					SDL_Rect* currentFrame = spriteAnimation->Frames[i];
					SDL_Rect* flippedFrame = new SDL_Rect;

					// Locate the flipped version on the sheet
					flippedFrame->x = SPRITES_SHEET_WIDTH - currentFrame->x - currentFrame->w;
					flippedFrame->y = currentFrame->y;
					flippedFrame->w = currentFrame->w;
					flippedFrame->h = currentFrame->h;

					spriteAnimation->Frames.push_back(flippedFrame);
				}
				
				// Add the finished animation object to the list
				SpriteAnimationList.push_back(spriteAnimation);
			}
			else
			{
				// Add new animation frame to current sequence
				SDL_Rect* frame = new SDL_Rect;

				frame->w = ReadLineValue(line, "W");
				frame->h = ReadLineValue(line, "H");
				frame->x = ReadLineValue(line, "X");
				frame->y = ReadLineValue(line, "Y");

				spriteAnimation->Frames.push_back(frame);
			}
		}
	}
}
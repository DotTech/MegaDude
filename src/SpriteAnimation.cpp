#include "SpriteAnimation.h"

//std::vector<SpriteAnimation*> SpriteAnimation::SpriteAnimationList;

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

// Load the spritesheets and initializes the sprite animations
void SpriteAnimation::InitAnimations()
{
	// IDLE SEQUENCE
	SpriteAnimation* spriteAnimation = new SpriteAnimation;
	spriteAnimation->CurrentFrame = 0;
	spriteAnimation->FrameRate = 150;

	// Repeat first frame 10 times
	for (int i=0; i<10; i++)
	{
		SDL_Rect* frame = new SDL_Rect;
		frame->x = 323;
		frame->y = 17;
		frame->w = 30;
		frame->h = 34;
		spriteAnimation->Frames.push_back(frame);
	}

	SDL_Rect* frame = new SDL_Rect;
	frame->x = 357;
	frame->y = 17;
	frame->w = 30;
	frame->h = 34;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 391;
	frame->y = 17;
	frame->w = 30;
	frame->h = 34;
	spriteAnimation->Frames.push_back(frame);

	// Load flipped frames
	spriteAnimation->TotalFrames = spriteAnimation->Frames.size();

	for (int i=0; i<spriteAnimation->TotalFrames; i++)
	{
		SDL_Rect* currentFrame = spriteAnimation->Frames[i];
		
		frame = new SDL_Rect;
		frame->x = SPRITES_SHEET_WIDTH - currentFrame->x - currentFrame->w;
		frame->y = currentFrame->y;
		frame->w = currentFrame->w;
		frame->h = currentFrame->h;
		spriteAnimation->Frames.push_back(frame);
	}

	SpriteAnimationList.push_back(spriteAnimation);



	// WALKING SEQUENCE

	// Open file with sprite definitions
	// 1::0=323,17:30,34;1=357,17:30,34;2=391,17:30,34
	spriteAnimation = new SpriteAnimation;
	spriteAnimation->CurrentFrame = 0;
	
	// Sprite definitions file only contains the frame locations for the sprite facing in one direction (flipped=false)
	// The flipped=true frame locations can be calculated using the previously loaded frames.
	// Formula for a flipped version of a frame X location is SPRITES_SHEET_WIDTH - FRAME_X - FRAME_WIDTH
	frame = new SDL_Rect;
	frame->x = 106;
	frame->y = 106;
	frame->w = 30;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 137;
	frame->y = 106;
	frame->w = 20;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 158;
	frame->y = 106;
	frame->w = 23;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 181;
	frame->y = 106;
	frame->w = 32;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 213;
	frame->y = 106;
	frame->w = 34;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 247;
	frame->y = 106;
	frame->w = 26;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 276;
	frame->y = 106;
	frame->w = 22;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 298;
	frame->y = 106;
	frame->w = 25;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 326;
	frame->y = 106;
	frame->w = 30;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 357;
	frame->y = 106;
	frame->w = 34;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 391;
	frame->y = 106;
	frame->w = 29;
	frame->h = 35;
	spriteAnimation->Frames.push_back(frame);

	
	// Load flipped frames
	spriteAnimation->TotalFrames = spriteAnimation->Frames.size();

	for (int i=0; i<spriteAnimation->TotalFrames; i++)
	{
		SDL_Rect* currentFrame = spriteAnimation->Frames[i];
		
		frame = new SDL_Rect;
		frame->x = SPRITES_SHEET_WIDTH - currentFrame->x - currentFrame->w;
		frame->y = currentFrame->y;
		frame->w = currentFrame->w;
		frame->h = currentFrame->h;
		spriteAnimation->Frames.push_back(frame);
	}

	spriteAnimation->FrameRate = 75;
	SpriteAnimationList.push_back(spriteAnimation);
}
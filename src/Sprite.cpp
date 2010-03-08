#include "Sprite.h"

std::vector<Sprite*> Sprite::SpriteList;

// Constructor
Sprite::Sprite()
{
	MovementRate = SPRITES_MOVEMENTRATE;
	LastMovementTick = 0;
	Width = 0;
	Height = 0;
	X = 0;
	Y = 0;

	// Load animation sequences
	SpriteAnimation::InitAnimations();
} 

// Start another animation sequence.
// eg. switch from SPRITES_MEGAMAN_IDLE to SPRITES_MEGAMAN_WALKING
void Sprite::SetSequence(int sequence)
{
	CurrentSequence = sequence;
	//CurrentFrame = 0;
}

// Destination rectangle. 
// This is where the current frame is drawn on the display surface
SDL_Rect Sprite::DestRect()
{
	SDL_Rect rect;

	rect.x = X + FrameOffsetX(Width);
	rect.y = Y;
	rect.w = Width;
	rect.h = Height;

	return rect;
}

// Create sprite objects
void Sprite::Init()
{
	// Create Megaman sprite
	Sprite* sprite = new Sprite;
	sprite->SetSequence(SPRITES_MEGAMAN_IDLE);
	sprite->Width = 35;
	sprite->Height = 35;
	sprite->Flipped = false;

	Sprite::SpriteList.push_back(sprite);
}
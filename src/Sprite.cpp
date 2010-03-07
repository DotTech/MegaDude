#include "Include\Sprite.h"

std::vector<Sprite*> Sprite::SpriteList;

// Constructor
Sprite::Sprite()
{
	FrameRate = SPRITES_FRAMERATE;
	CurrentFrame = 0;
	Width = 0;
	Height = 0;
	X = 0;
	Y = 0;
} 


// Frames dont always have the same width. 
// This offset is the amount of pixels needed to put the frame in the center of the sprite.
int Sprite::FrameOffsetX()
{
	int offset = 0;
	int frameWidth = Frames[CurrentFrame]->w;

	if (frameWidth <= Width - 2)
	{
		offset = Width - frameWidth;
		offset = offset / 2;
	}
	
	return offset;
}


// Destination rectangle. 
// This is where the current frame is drawn on the display surface
SDL_Rect Sprite::DestRect()
{
	SDL_Rect rect;

	rect.x = X + FrameOffsetX();
	rect.y = Y;
	rect.w = Width;
	rect.h = Height;

	return rect;
}


// Load the spritesheets and initializes the sprite objects
void Sprite::InitSprites()
{
	// Open file with sprite definitions
	// 1::0=323,17:30,34;1=357,17:30,34;2=391,17:30,34
	Sprite* sprite = new Sprite;
	sprite->CurrentFrame = 0;
	sprite->Width = 35;
	sprite->Height = 35;
	

	/*
	SDL_Rect* frame1 = new SDL_Rect;
	frame1->x = 323;
	frame1->y = 17;
	frame1->w = 30;
	frame1->h = 34;

	SDL_Rect* frame2 = new SDL_Rect;
	frame2->x = 357;
	frame2->y = 17;
	frame2->w = 30;
	frame2->h = 34;

	SDL_Rect* frame3 = new SDL_Rect;
	frame3->x = 391;
	frame3->y = 17;
	frame3->w = 30;
	frame3->h = 34;
	*/

	SDL_Rect* frame = new SDL_Rect;
	frame->x = 106;
	frame->y = 106;
	frame->w = 30;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 137;
	frame->y = 106;
	frame->w = 20;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 158;
	frame->y = 106;
	frame->w = 23;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 181;
	frame->y = 106;
	frame->w = 32;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 213;
	frame->y = 106;
	frame->w = 34;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 247;
	frame->y = 106;
	frame->w = 26;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 276;
	frame->y = 106;
	frame->w = 22;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 298;
	frame->y = 106;
	frame->w = 25;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 326;
	frame->y = 106;
	frame->w = 30;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 357;
	frame->y = 106;
	frame->w = 34;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	frame = new SDL_Rect;
	frame->x = 391;
	frame->y = 106;
	frame->w = 29;
	frame->h = 35;
	sprite->Frames.push_back(frame);

	//sprite->Frames.push_back(frame2);
	//sprite->Frames.push_back(frame3);

	Sprite::SpriteList.push_back(sprite);
}
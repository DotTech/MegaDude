#include "Entity.h"

std::vector<Entity*> Entity::EntityList;

// Constructor
Entity::Entity()
{
	MovementRate = SPRITES_MOVEMENTRATE;
	LastMovementTick = 0;
	Width = 0;
	Height = 0;
	X = 0;
	Y = 0;
	Direction = false;
} 

// Destination rectangle. 
// This is where the current frame is drawn on the display surface
SDL_Rect Entity::FrameDestRect()
{
	SDL_Rect rect;

	rect.x = X + Animation->FrameOffsetX(Width);
	rect.y = Y + Animation->FrameOffsetY(Height);
	rect.w = Width;
	rect.h = Height;

	return rect;
}

// Create sprite objects
void Entity::Init()
{
	// Create Megaman sprite
	Entity* entity = new Entity;
	entity->SetAnimation(SPRITES_MEGAMAN_IDLE, true);
	entity->Width = 35;
	entity->Height = 46;
	entity->Animation->Flipped = false;

	Entity::EntityList.push_back(entity);
}

// Set another sprite animation sequence (eg SPRITES_MEGAMAN_WALK or SPRITES_MEGAMAN_JUMP)
void Entity::SetAnimation(int sequence, bool resetCurrentFrame)	
{
	// TODO: Make copy
	Animation = SpriteAnimation::SpriteAnimationList[sequence];
	CurrentAnimation = sequence;
	Animation->Flipped = Direction;

	if (resetCurrentFrame)
	{
		Animation->CurrentFrame = 0;
		Animation->LastAnimationTick = SDL_GetTicks();
	}
}
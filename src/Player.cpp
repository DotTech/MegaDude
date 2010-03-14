#include "Player.h"

Player::Player(void)
{
	Entity = NULL;
	Jumping = false;
	Walking = false;
	Shooting = false;
	LastJumpTick = 0;
	JumpingState = None;
}

// Returns true of player is going left, false if its going right
bool Player::GetDirection()
{
	return Entity->Direction;
}

// Set the direction the player is facing to
void Player::SetDirection(bool left)
{	
	Entity->Animation->Flipped = left;
	Entity->Direction = left;
}

// Handle player movement logic
void Player::Move()
{
	if (Entity->LastMovementTick == 0 ||  SDL_GetTicks() - Entity->LastMovementTick >= (unsigned int)Entity->MovementRate)
	{
		if (Walking)
			Walk();
		
		// Player is idle, let it blink with its eyes
		if (!Walking && !Jumping)
		{
			if (Entity->CurrentAnimation != SPRITES_MEGAMAN_IDLE)
				Entity->SetAnimation(SPRITES_MEGAMAN_IDLE, true);	
		}

		// Remember when we moved
		Entity->LastMovementTick = SDL_GetTicks();
	}

	if (LastJumpTick == 0 ||  SDL_GetTicks() - LastJumpTick >= (unsigned int)JUMP_SPEED)
	{
		if (Jumping)
			Jump();

		LastJumpTick = SDL_GetTicks();
	}
}

// Handle player walk logic
void Player::Walk()
{
	// If we are not jumping and walking animation has not been set yet, set the walking animation
	if (!Jumping && Entity->CurrentAnimation != SPRITES_MEGAMAN_WALK)
		Entity->SetAnimation(SPRITES_MEGAMAN_WALK, true);

	if (GetDirection())
		Entity->X--;
	else
		Entity->X++;
}

// Handle player jump logic
void Player::Jump()
{
	// If we just entered the jumping state, we need to reset the currentframe to 0
	if (Entity->CurrentAnimation != SPRITES_MEGAMAN_JUMP_UP 
		&& Entity->CurrentAnimation != SPRITES_MEGAMAN_JUMP_HANG 
		&& Entity->CurrentAnimation != SPRITES_MEGAMAN_JUMP_TOUCHDOWN
		|| JumpingState == Player::End)
	{
		Entity->SetAnimation(SPRITES_MEGAMAN_JUMP_UP, true);
		JumpingState = Player::GoingUp;
		_jumpAcceleration = JUMP_ACCELERATION;
		_jumpedHeight = 0;
	}

	// Move the player entity up
	if (JumpingState == Player::GoingUp)
	{
		Entity->Y -= _jumpAcceleration;
		_jumpedHeight += _jumpAcceleration;

		// Make us move up slower after each movement
		// This creates the feeling of gravity
		if (_jumpAcceleration > 1)
			_jumpAcceleration--;

		if (_jumpedHeight >= JUMP_MAXHEIGHT)
			JumpingState = Player::Falling;
	}

	// Move the player entity down when falling
	if (JumpingState == Player::Falling)
	{
		if (Entity->Y + _jumpAcceleration <= TEMP_GROUND_Y - 20)
		{
			// Change the animation when we fall down
			if (Entity->CurrentAnimation != SPRITES_MEGAMAN_JUMP_HANG)
				Entity->SetAnimation(SPRITES_MEGAMAN_JUMP_HANG, true);

			Entity->Y += _jumpAcceleration;
		}
		else if (Entity->Y + _jumpAcceleration <= TEMP_GROUND_Y)
		{
			// Change the animation when we almost touch the ground
			if (Entity->CurrentAnimation != SPRITES_MEGAMAN_JUMP_TOUCHDOWN)
				Entity->SetAnimation(SPRITES_MEGAMAN_JUMP_TOUCHDOWN, true);

			Entity->Y += _jumpAcceleration;
		}
		else
		{
			// Player touched down, end the jump
			Jumping = false;
			JumpingState = Player::End;
			Entity->Y = TEMP_GROUND_Y;
		}

		// Make us move down fast after each movement
		// This creates the feeling of gravity
		if (_jumpAcceleration < JUMP_ACCELERATION)
			_jumpAcceleration++;
	}
}
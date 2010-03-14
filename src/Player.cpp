#include "Player.h"

Player::Player(void)
{
	Entity = NULL;
	Jumping = false;
	Walking = false;
	Shooting = false;
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
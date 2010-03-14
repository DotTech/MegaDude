#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include "Definitions.h"
#include "Entity.h" 

class Player
{
public:
	Entity* Entity;
	bool Walking;
	bool Jumping;
	bool Shooting;

	Player(void);
	void SetDirection(bool left);
	bool GetDirection();	// false=right, true=left
};

#endif
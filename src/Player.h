#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include "Definitions.h"
#include "Entity.h" 

class Player
{
private:
	int _jumpAcceleration;
	int _jumpedHeight;
	void Walk();
	void Jump();

public:
	// The jumping states
	enum JumpState
	{
		None,
		GoingUp,
		Falling,
		End
	};

	Entity* Entity;
	bool Walking;
	bool Jumping;
	bool Shooting;
	JumpState JumpingState;
	Uint32 LastJumpTick;	// Ticks value at last jump movement

	Player(void);
	void SetDirection(bool left);
	bool GetDirection();	// false=right, true=left
	void Move();
};

#endif
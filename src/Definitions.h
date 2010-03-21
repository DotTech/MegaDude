//  MODULE NAME: Definitions.h
//      PROJECT: SDL-based 2D Platform Game
//       AUTHOR: Ruud van Falier
//               ruud.vanfalier@gmail.com
//         DATE: March 9, 2010
//  DESCRIPTION: Contains all used definitions and typedefs

#pragma once
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include <SDL.h>

#define RESOLUTION_WIDTH	320
#define RESOLUTION_HEIGHT	240
#define SCALE2X				true

#define SPRITES_SHEET_WIDTH				1076	// Width of spritesheet
#define SPRITES_SHEET_HEIGHT			930		// Height of spritesheet
#define SPRITES_FRAMERATE				75		// Default animation speed
#define SPRITES_MOVEMENTRATE			5		// Default sprite movement speed
#define SPRITES_TRANSPARANCY_R			255		// Transparancy color R value
#define SPRITES_TRANSPARANCY_G			0		// Transparancy color G value
#define SPRITES_TRANSPARANCY_B			233		// Transparancy color B value
#define SPRITES_MEGAMAN					0		// Megaman Sprite
#define SPRITES_MEGAMAN_IDLE			0		// Megaman idle sequence
#define SPRITES_MEGAMAN_WALK			1		// Megaman walking sequence
#define SPRITES_MEGAMAN_JUMP_UP			2		// Megaman jumping going up
#define SPRITES_MEGAMAN_JUMP_HANG		3		// Megaman jumping hanging/falling
#define SPRITES_MEGAMAN_JUMP_TOUCHDOWN	4		// Megaman jumping touching down

#define TILES_WIDTH		16
#define TILES_HEIGHT	16

#define JUMP_ACCELERATION	10		// Acceleration when jumping
#define JUMP_MAXHEIGHT		60		// Maximum height of a jump
#define JUMP_SPEED			50		// Movement speed while jumping

#define TEMP_GROUND_Y		178

#define DATAFILE_TITLESCREEN "d:\\Data\\MegaDude\\src\\data\\titlescreen.bmp"
#define DATAFILE_SPRITESHEET "d:\\Data\\MegaDude\\src\\data\\sprites.bmp"
#define DATAFILE_CONSOLEFONT "d:\\Data\\MegaDude\\src\\data\\ConsoleFont.bmp"
#define DATAFILE_ANIMATIONSDEF "d:\\Data\\MegaDude\\src\\data\\animations.txt"
#define DATAFILE_SPRITESDEF "d:\\Data\\MegaDude\\src\\data\\sprites.txt"
#define DATAFILE_TILESDEF "d:\\Data\\MegaDude\\src\\data\\tiles.txt"

// The different game states (startup, titlescreen, playing, etc)
enum GameState
{
	TitleScreen,
	PlayingLevel,
	GameOver
};

// State of the keys used during gameplay (pressed=true, released=false)
typedef struct GameKeysState
{
	bool LeftKeyDown;
	bool RightKeyDown;
	bool JumpKeyDown;
	bool ShootKeyDown;
	bool ConsoleKeyDown;
} GameKeysState;

// Contains SDL_Surfaces that stay in-memory during gameplay
typedef struct Surfaces
{
	SDL_Surface* Display;
	SDL_Surface* DisplayBuffer;
	SDL_Surface* Sprites;
	SDL_Surface* Tiles;
	SDL_Surface* TitleScreen;
} Surfaces;

// Console state structure
typedef struct ConsoleState
{
	int LastTick;
	bool Enabled;
} ConsoleState;

#endif
#pragma once
#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
#include <string>
#include <fstream>
#include <SDL.h>
#include "Definitions.h"

using namespace std;

class Tile
{
private:
	static int ReadLineValue(string line, string key);	// Read a key value from an animation definition line

public:
	static vector<Tile*> TileList;	// Locations of the tiles on the spritesheet
	SDL_Rect TileRect;

public:
	Tile(void);
	static void Init();			// Initialize tile data
};

#endif
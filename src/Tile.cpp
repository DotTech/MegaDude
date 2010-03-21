#include "Tile.h"

std::vector<Tile*> Tile::TileList;

Tile::Tile(void)
{
}

// Read a key value from an tile definition line
int Tile::ReadLineValue(string line, string key)
{
	key += ":";

	// Find the key trailed by colon sign
	int startPos = line.find(key);
	if (startPos != string.npos)
	{
		startPos += key.length();
		line = line.substr(startPos, line.length() - startPos);

		// Find semicolon
		int scolonPos = line.find_first_of(";");

		// Return the found value
		return atoi(line.substr(0, scolonPos).c_str());
	}

	return -1;
}

// Load the spritesheets and initializes the sprite animations
void Tile::Init()
{
	// Load tile definition file into string vector
	vector<string> definition;
	ifstream file(DATAFILE_TILESDEF);
	
	string line;
	while (getline(file, line))
	{
		definition.push_back(line);
	}
	
	for (int i=0; i<(int)definition.size(); i++)
	{
		line = definition[i];
		
		// Skip comments and empty lines
		if (line.length() > 0 && line.substr(0, 2) != "//")
		{
			Tile* tile = new Tile;
			tile->TileRect.w = TILES_WIDTH;
			tile->TileRect.h = TILES_HEIGHT;
			tile->TileRect.x = ReadLineValue(line, "X");
			tile->TileRect.y = ReadLineValue(line, "Y");

			Tile::TileList.push_back(tile);
		}
	}
}
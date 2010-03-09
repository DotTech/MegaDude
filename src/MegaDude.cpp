//  MODULE NAME: MegaDude.cpp
//      PROJECT: SDL-based 2D Platform Game
//       AUTHOR: Ruud van Falier
//               ruud.vanfalier@gmail.com
//         DATE: March 4, 2010
//  DESCRIPTION: Main game class. 
//               Call Execute() to start the game

#include "MegaDude.h"


// Application entrance point
int main(int argc, char* argv[]) 
{
	MegaDude game;
    return game.Execute();
}

// Class constructor
MegaDude::MegaDude(void)
{
	// Reset surfaces
	_surfaces.Display = NULL;
	_surfaces.Sprites = NULL;
	_surfaces.Tiles = NULL;

	// Reset gamekeysstates
	_gameKeysState.LeftKeyDown = false;
	_gameKeysState.RightKeyDown = false;
	_gameKeysState.ShootKeyDown = false;
	_gameKeysState.JumpKeyDown = false;

	_gameRunning = true;
	_gameState = PlayingLevel;
}

// Executes the game
int MegaDude::Execute()
{
	SDL_Event polledEvent;
	
	// Initialize SDL
	if (!Init())
	{
		return -1;
	}
	
	// Start game loop
	while (_gameRunning)
	{
		// Poll SDL for events and handle them
		// When gamekeys are pressed or released the _gameKeysState is updated
		SDL_PollEvent(&polledEvent);
		SdlEvents::OnEvent(&polledEvent);
		
		// Act on pressed or released gamekeys
		HandleGameKeys();

		// Do all game calculations
		Calculate();

		// Render graphics
		Render();
	}
	
	// Cleanup objects before quitting
	Cleanup();
	
	return 0;
}

// Handles all the loading of data, whether it be textures, 
// maps, NPCs, or whatever.
bool MegaDude::Init()
{
	// SDL initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	
	// Display surface initialization
	if ((_surfaces.Display  = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE || SDL_DOUBLEBUF)) == NULL)
		return false;
	
	// Window title
	SDL_WM_SetCaption("MegaDude", NULL);

	// Load titlescreen surface
	SDL_Surface* loadingSurface = SDL_LoadBMP(DATAFILE_TITLESCREEN);
	_surfaces.TitleScreen = SDL_DisplayFormat(loadingSurface);
	
	// Load spritesheet to surface and setup transparancy
	loadingSurface = SDL_LoadBMP(DATAFILE_SPRITESHEET);
	_surfaces.Sprites = SDL_DisplayFormat(loadingSurface);
	SDL_SetColorKey(_surfaces.Sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(_surfaces.Sprites->format, SPRITES_TRANSPARANCY_R, SPRITES_TRANSPARANCY_G, SPRITES_TRANSPARANCY_B));

	// Initialize sprite data
	// This loads the definition of animation frames and their location on the spritesheet
	Sprite::Init();
	
	// Create player entity
	// TODO: Move entity creation to other class
	_player = Sprite::SpriteList[SPRITES_MEGAMAN];
	_player->SetSequence(SPRITES_MEGAMAN_IDLE);

	// Free up temporary surface
	SDL_FreeSurface(loadingSurface);

	// Initialize console
	_console = CON_Init(DATAFILE_CONSOLEFONT, _surfaces.Display, 100, *new SDL_Rect);

	return true;
}

// Act on pressed or released gamekeys
void MegaDude::HandleGameKeys()
{
	if (_player->LastMovementTick == 0 ||  SDL_GetTicks() - _player->LastMovementTick >= (unsigned int)_player->MovementRate)
	{
		// Walk left or right
		if (_gameKeysState.RightKeyDown)
		{
			_player->SetSequence(SPRITES_MEGAMAN_WALK);
			_player->Flipped = false;
			_player->X++;
		}
		else if (_gameKeysState.LeftKeyDown)
		{
			_player->SetSequence(SPRITES_MEGAMAN_WALK);
			_player->Flipped = true;
			_player->X--;
		}
		
		// Remember when we moved
		_player->LastMovementTick = SDL_GetTicks();
	}
	
	// If no gamekey is active, show megaman in idle state
	if (!_gameKeysState.LeftKeyDown && !_gameKeysState.RightKeyDown)
	{
		if (_player->CurrentSequence != SPRITES_MEGAMAN_IDLE)
		{
			_player->SetSequence(SPRITES_MEGAMAN_IDLE);	
		}
	}
}

// Handles all the data updates, such as a NPCs moving across the screen, 
// decreasing your health bar, or whatever
void MegaDude::Calculate()
{
	// Move player
	_player->DoAnimation();
}

// Handles all the rendering of anything that shows up on the screen. 
// It does NOT handle data manipulation, 
// as this is what the Calculate function is supposed to handle.
void MegaDude::Render()
{
	SDL_Rect rectDest;
	rectDest.x = 0;
	rectDest.y = 0;

	SDL_BlitSurface(_surfaces.TitleScreen, NULL, _surfaces.Display, &rectDest);
	
	// Draw the player sprite
	SDL_BlitSurface(_surfaces.Sprites, &_player->GetCurrentFrame(), _surfaces.Display, &_player->DestRect());

	// Render console
	SDL_Rect border;
	border.x = 723; border.y = 467;
	border.w = 300; border.h = 300;

	SDL_FillRect(_surfaces.Display, &border, 0);
	CON_DrawConsole(_console);

	char spriteX[10];
	sprintf_s(spriteX, "%d", _player->X);

	DT_DrawText("Debug console", _surfaces.Display, 0, 740, 480);
	DT_DrawText(spriteX, _surfaces.Display, 0, 740, 500);

	// Flip the display surface
	SDL_Flip(_surfaces.Display);
}

// Cleans up any resources loaded, and insures a peaceful quitting of the game.
void MegaDude::Cleanup()
{
	SDL_FreeSurface(_surfaces.Display);
	SDL_FreeSurface(_surfaces.Tiles);
	SDL_FreeSurface(_surfaces.TitleScreen);
	SDL_FreeSurface(_surfaces.Sprites);

	// TODO: Cleanup all animation and sprite data
	// The rect objects are all created on the heap and will stay there if we dont destroy them

	SDL_Quit();
}


/********************************************************************************
 * GameEvents methods implementations											*
 *******************************************************************************/

// A key is being pressed
void MegaDude::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
	if (sym == SDLK_LEFT)
	{
		_gameKeysState.RightKeyDown = false;
		_gameKeysState.LeftKeyDown = true;
	}

	if (sym == SDLK_RIGHT)
	{
		_gameKeysState.LeftKeyDown = false;
		_gameKeysState.RightKeyDown = true;
	}
		
	if (sym == SDLK_ESCAPE)
	{
		OnExit();
	}
}

// A key was released
void MegaDude::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_LEFT) _gameKeysState.LeftKeyDown = false;
	if (sym == SDLK_RIGHT) _gameKeysState.RightKeyDown = false;
}

// Escape pressed or window closed
void MegaDude::OnExit()
{
	_gameRunning = false;
}
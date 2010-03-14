//  MODULE NAME: MegaDude.cpp
//      PROJECT: SDL-based 2D Platform Game
//       AUTHOR: Ruud van Falier
//               ruud.vanfalier@gmail.com
//         DATE: March 4, 2010
//  DESCRIPTION: Main game class. 
//               Call Execute() to start the game

#include "MegaDude.h"

// pointer to the line in VRAM to start blitting to when stretchblitting.
// this may not be the first line on the display as it is adjusted to
// center the image on the screen when in fullscreen.
unsigned char *VRAMPtr;

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
	if (!SCALE2X)
	{
		if ((_surfaces.Display  = SDL_SetVideoMode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 32, SDL_HWSURFACE || SDL_DOUBLEBUF)) == NULL)
			return false;
	}
	else
	{
		if ((_surfaces.Display  = SDL_SetVideoMode(RESOLUTION_WIDTH * 2, RESOLUTION_HEIGHT * 2, 32, SDL_HWSURFACE || SDL_DOUBLEBUF)) == NULL)
    		return false;
	}
	
	_surfaces.DisplayBuffer = SDL_DisplayFormat(_surfaces.Display);
	_surfaces.DisplayBuffer->w = RESOLUTION_WIDTH;
	_surfaces.DisplayBuffer->h = RESOLUTION_HEIGHT;

	// Window title
	SDL_WM_SetCaption("MegaDude", NULL);

	// Load titlescreen surface
	SDL_Surface* loadingSurface = SDL_LoadBMP(DATAFILE_TITLESCREEN);
	_surfaces.TitleScreen = SDL_DisplayFormat(loadingSurface);

	// Replace titlescreen with white rectangle
	SDL_Rect rect;
	rect.x = 0; rect.y = 0;
	rect.w = 1024; rect.h = 768;
	SDL_FillRect(_surfaces.TitleScreen, &rect, SDL_MapRGB(_surfaces.TitleScreen->format, 0xFF, 0xFF, 0xFF));
	
	rect.x = 0; rect.y = TEMP_GROUND_Y + 46;
	rect.w = 1024; rect.h = 10;
	SDL_FillRect(_surfaces.TitleScreen, &rect, SDL_MapRGB(_surfaces.TitleScreen->format, 0xCC, 0x00, 0x00));

	// Load spritesheet to surface and setup transparancy
	loadingSurface = SDL_LoadBMP(DATAFILE_SPRITESHEET);
	_surfaces.Sprites = SDL_DisplayFormat(loadingSurface);
	SDL_SetColorKey(_surfaces.Sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(_surfaces.Sprites->format, SPRITES_TRANSPARANCY_R, SPRITES_TRANSPARANCY_G, SPRITES_TRANSPARANCY_B));


	SpriteAnimation::InitAnimations();

	// Initialize sprite data
	// This loads the definition of animation frames and their location on the spritesheet
	Entity::Init();
	
	// Create player entity
	// TODO: Move entity creation to other class
	_player = new Player();
	_player->Entity = Entity::EntityList[SPRITES_MEGAMAN];
	_player->Entity->SetAnimation(SPRITES_MEGAMAN_IDLE, true);
	_player->Entity->Y = TEMP_GROUND_Y;

	// TODO: Temp NPC, remove
	_testNpc = new Player();
	_testNpc->Entity = Entity::EntityList[1];
	_testNpc->Entity->SetAnimation(SPRITES_MEGAMAN_WALK, true);
	_testNpc->Entity->Y = TEMP_GROUND_Y;
	_testNpc->Entity->X = 700;

	// Free up temporary surface
	SDL_FreeSurface(loadingSurface);

	// Initialize console
	_console = CON_Init(DATAFILE_CONSOLEFONT, _surfaces.DisplayBuffer, 100, *new SDL_Rect);

	return true;
}

// Act on pressed or released gamekeys
void MegaDude::HandleGameKeys()
{
	// Walking keys handling
	if (_gameKeysState.RightKeyDown || _gameKeysState.LeftKeyDown)
	{
		_player->Walking = true;
		_player->SetDirection(_gameKeysState.LeftKeyDown);
	}
	else
	{
		_player->Walking = false;
	}
	
	// Jump key handling
	if (_gameKeysState.JumpKeyDown)
	{
		_player->Jumping = true;
	}
	else 
	{ 
		_player->JumpingState = Player::Falling;
		//_player->Jumping = false; 
	}
}

// Handles all the data updates, such as a NPCs moving across the screen, 
// decreasing your health bar, or whatever
void MegaDude::Calculate()
{
	// Handles player animation sequence
	_player->Entity->Animation->DoAnimation();

	// Handle player movement
	_player->Move();


	_testNpc->Entity->Animation->DoAnimation();

}

// Handles all the rendering of anything that shows up on the screen. 
// It does NOT handle data manipulation, 
// as this is what the Calculate function is supposed to handle.
void MegaDude::Render()
{
	SDL_Rect rectDest;
	rectDest.x = 0;
	rectDest.y = 0;

	SDL_BlitSurface(_surfaces.TitleScreen, NULL, _surfaces.DisplayBuffer, &rectDest);
	
	// Draw the player sprite
	SDL_BlitSurface(_surfaces.Sprites, &_player->Entity->Animation->GetCurrentFrame(), _surfaces.DisplayBuffer, &_player->Entity->FrameDestRect());

	// Draw the player sprite
	SDL_BlitSurface(_surfaces.Sprites, &_testNpc->Entity->Animation->GetCurrentFrame(), _surfaces.DisplayBuffer, &_testNpc->Entity->FrameDestRect());

	// Render console
	SDL_Rect border;
	border.x = 723; border.y = 467;
	border.w = 300; border.h = 300;

	SDL_FillRect(_surfaces.DisplayBuffer, &border, 0);
	CON_DrawConsole(_console);

	char spriteX[80];
	sprintf_s(spriteX, "x:%d fr:%d cf:%d", _player->Entity->X, _player->Entity->Animation->FrameRate, _player->Entity->Animation->CurrentFrame);

	DT_DrawText("Debug console", _surfaces.DisplayBuffer, 0, 740, 480);
	DT_DrawText(spriteX, _surfaces.DisplayBuffer, 0, 740, 500);

	// Debug: display key strokes
	if (_gameKeysState.LeftKeyDown) DT_DrawText("LEFT", _surfaces.DisplayBuffer, 0, 740, 520);
	if (_gameKeysState.RightKeyDown) DT_DrawText("RIGHT", _surfaces.DisplayBuffer, 0, 780, 520);
	if (_player->Walking) DT_DrawText("walking", _surfaces.DisplayBuffer, 0, 740, 540);
	if (_gameKeysState.JumpKeyDown) DT_DrawText("JUMP", _surfaces.DisplayBuffer, 0, 820, 520);
	if (_player->Jumping) DT_DrawText("jumping", _surfaces.DisplayBuffer, 0, 820, 540);

	// Blit a scaled version of the displaybuffer to the display surface
	if (SCALE2X)
	{
		Scale2X::Scale(_surfaces.DisplayBuffer, _surfaces.Display);
	}
	else
	{
		SDL_BlitSurface(_surfaces.DisplayBuffer, NULL, _surfaces.Display, NULL);
	}

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
	
	if (sym == SDLK_LCTRL)
	{
		_gameKeysState.JumpKeyDown = true;
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
	if (sym == SDLK_LCTRL) _gameKeysState.JumpKeyDown = false;
}

// Escape pressed or window closed
void MegaDude::OnExit()
{
	_gameRunning = false;
}
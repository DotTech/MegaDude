//  MODULE NAME: SdlGame.cpp
//      PROJECT: SDL Platform Game
//       AUTHOR: Ruud van Falier
//				 ruud.vanfalier@gmail.com
//         DATE: March 4, 2010
//  DESCRIPTION: -

#include "MegaDude.h"
#include "SDL_Console\DT_Drawtext.h"
#include "SDL_Console\SDL_Console.h"

ConsoleInformation* Console;
int fps;

// Application entrance point
int main(int argc, char* argv[]) 
{
	MegaDude game;
    return game.Execute();
}


// Class constructor
MegaDude::MegaDude(void)
{
	_displaySurface = NULL;
	_spriteSurface = NULL;
	_running = true;
}


// Executes the game
int MegaDude::Execute()
{
	SDL_Event sdlEvent;

	// Initialize SDL
	if (!Init())
	{
		return -1;
	}

	// Start game loop
	while (_running)
	{
		// Poll SDL for events and handle them
		while (SDL_PollEvent(&sdlEvent))
		{
			HandleEvents(&sdlEvent);
		}

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
	{
		return false;
	}

	// Display surface initialization
	if ((_displaySurface = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE || SDL_DOUBLEBUF)) == NULL)
	{
		return false;
	}
	
	// Window title
	SDL_WM_SetCaption("MegaDude", NULL);

	// TEMP: Draw title screen
	SDL_Surface* loadingSurface = SDL_LoadBMP(DATAFILE_TITLESCREEN);
	_bgSurface = SDL_DisplayFormat(loadingSurface);
	

	// Initialize game sprite data
	Sprite::InitSprites();
	
	// Load spritesheet to surface
	loadingSurface = SDL_LoadBMP(DATAFILE_SPRITESHEET);
	_spriteSurface = SDL_DisplayFormat(loadingSurface);
	
	// Setup transparancy on sprite surface
	SDL_SetColorKey(_spriteSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(_spriteSurface->format, SPRITES_TRANSPARANCY_R, SPRITES_TRANSPARANCY_G, SPRITES_TRANSPARANCY_B));
	
	// Free up temporary surface
	SDL_FreeSurface(loadingSurface);

	// Initialize console
	Console = CON_Init(DATAFILE_CONSOLEFONT, _displaySurface, 100, *new SDL_Rect);

	return true;
}


// Handles all input events from the mouse, keyboard, 
// joysticks, or other devices.
void MegaDude::HandleEvents(SDL_Event* sdlEvent)
{
	SdlEvents::OnEvent(sdlEvent);
}


// Handles all the data updates, such as a NPCs moving across the screen, 
// decreasing your health bar, or whatever
void MegaDude::Calculate()
{
	if (_lastTick == 0 ||  SDL_GetTicks() - _lastTick >= 75)
	{
		if (Sprite::SpriteList[0]->CurrentFrame < 9)
			Sprite::SpriteList[0]->CurrentFrame++;
		else
			Sprite::SpriteList[0]->CurrentFrame = 0;
		
		_lastTick = SDL_GetTicks();
	}
}


// Handles all the rendering of anything that shows up on the screen. 
// It does NOT handle data manipulation, 
// as this is what the Calculate function is supposed to handle.
void MegaDude::Render()
{
	SDL_Rect rectDest;
	rectDest.x = 0;
	rectDest.y = 0;

	SDL_BlitSurface(_bgSurface, NULL, _displaySurface, &rectDest);

	SDL_Rect border;
	border.x = 723;
	border.y = 467;
	border.w = 300;
	border.h = 300;

	SDL_FillRect(_bgSurface, &border, 0);
	
	

	Sprite* testSprite = Sprite::SpriteList[0];
	
	SDL_BlitSurface(_spriteSurface, testSprite->Frames[testSprite->CurrentFrame], _displaySurface, &testSprite->DestRect());

	// Render console
	CON_DrawConsole(Console);
	DT_DrawText("Debug console", _displaySurface, 0, 740, 480);

	SDL_Flip(_displaySurface);
}


// Cleans up any resources loaded, and insures a peaceful quitting of the game.
void MegaDude::Cleanup()
{
	SDL_FreeSurface(_displaySurface);
	SDL_FreeSurface(_spriteSurface);
	SDL_Quit();
}



/********************************************************************************
 * GameEvents virtual method implementations									*
 *******************************************************************************/

void MegaDude::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
	if (sym == SDLK_ESCAPE)
	{
		OnExit();
	}
}


void MegaDude::OnExit()
{
	_running = false;
}
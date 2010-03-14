#include "SdlEvents.h"

SdlEvents::SdlEvents(void)
{
}

SdlEvents::~SdlEvents(void)
{
}

void SdlEvents::OnEvent(SDL_Event* sdlEvent) 
{
    switch(sdlEvent->type) 
	{
        case SDL_ACTIVEEVENT:
            switch(sdlEvent->active.state) 
			{
                case SDL_APPMOUSEFOCUS:
                    if ( sdlEvent->active.gain )   OnMouseFocus();
                    else                OnMouseBlur();

                    break;
                case SDL_APPINPUTFOCUS:
                    if ( sdlEvent->active.gain )   OnInputFocus();
                    else                OnInputBlur();

                    break;
                case SDL_APPACTIVE:
                    if ( sdlEvent->active.gain )   OnRestore();
                    else                OnMinimize();

                    break;
            }
            break;

        case SDL_KEYDOWN:
            OnKeyDown(sdlEvent->key.keysym.sym,sdlEvent->key.keysym.mod,sdlEvent->key.keysym.unicode);
            break;
       
        case SDL_KEYUP:
            OnKeyUp(sdlEvent->key.keysym.sym,sdlEvent->key.keysym.mod,sdlEvent->key.keysym.unicode);
            break;

        case SDL_MOUSEMOTION:
            OnMouseMove(sdlEvent->motion.x,sdlEvent->motion.y,sdlEvent->motion.xrel,sdlEvent->motion.yrel,(sdlEvent->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(sdlEvent->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(sdlEvent->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(sdlEvent->button.button) 
			{
                case SDL_BUTTON_LEFT:
                    OnLButtonDown(sdlEvent->button.x,sdlEvent->button.y);
                    break;
                case SDL_BUTTON_RIGHT:
                    OnRButtonDown(sdlEvent->button.x,sdlEvent->button.y);
                    break;
                case SDL_BUTTON_MIDDLE:
                    OnMButtonDown(sdlEvent->button.x,sdlEvent->button.y);
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch(sdlEvent->button.button) 
			{
                case SDL_BUTTON_LEFT:
                    OnLButtonUp(sdlEvent->button.x,sdlEvent->button.y);
                    break;
                case SDL_BUTTON_RIGHT:
                    OnRButtonUp(sdlEvent->button.x,sdlEvent->button.y);
                    break;
                case SDL_BUTTON_MIDDLE:
                    OnMButtonUp(sdlEvent->button.x,sdlEvent->button.y);
                    break;
            }
            break;

        case SDL_JOYAXISMOTION:
            OnJoyAxis(sdlEvent->jaxis.which,sdlEvent->jaxis.axis,sdlEvent->jaxis.value);
            break;

        case SDL_JOYBALLMOTION:
            OnJoyBall(sdlEvent->jball.which,sdlEvent->jball.ball,sdlEvent->jball.xrel,sdlEvent->jball.yrel);
            break;

        case SDL_JOYHATMOTION:
            OnJoyHat(sdlEvent->jhat.which,sdlEvent->jhat.hat,sdlEvent->jhat.value);
            break;

        case SDL_JOYBUTTONDOWN:
            OnJoyButtonDown(sdlEvent->jbutton.which,sdlEvent->jbutton.button);
            break;

        case SDL_JOYBUTTONUP:
            OnJoyButtonUp(sdlEvent->jbutton.which,sdlEvent->jbutton.button);
            break;

        case SDL_QUIT:
            OnExit();
            break;

        case SDL_SYSWMEVENT:
            //Ignore
            break;

        case SDL_VIDEORESIZE:
            OnResize(sdlEvent->resize.w,sdlEvent->resize.h);
            break;

        case SDL_VIDEOEXPOSE:
            OnExpose();
            break;

        default:
            OnUser(sdlEvent->user.type,sdlEvent->user.code,sdlEvent->user.data1,sdlEvent->user.data2);
            break;
    }
}

void SdlEvents::OnInputFocus() 
{
}

void SdlEvents::OnInputBlur() 
{
}

void SdlEvents::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void SdlEvents::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
}

void SdlEvents::OnMouseFocus() 
{
}

void SdlEvents::OnMouseBlur() 
{
}

void SdlEvents::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) 
{
}

void SdlEvents::OnMouseWheel(bool Up, bool Down) 
{
}

void SdlEvents::OnLButtonDown(int mX, int mY) 
{
}

void SdlEvents::OnLButtonUp(int mX, int mY) 
{
}

void SdlEvents::OnRButtonDown(int mX, int mY) 
{
}

void SdlEvents::OnRButtonUp(int mX, int mY) 
{
}

void SdlEvents::OnMButtonDown(int mX, int mY) 
{
}

void SdlEvents::OnMButtonUp(int mX, int mY) 
{
}

void SdlEvents::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) 
{
}

void SdlEvents::OnJoyButtonDown(Uint8 which,Uint8 button) 
{
}

void SdlEvents::OnJoyButtonUp(Uint8 which,Uint8 button) 
{
}

void SdlEvents::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) 
{
}

void SdlEvents::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) 
{
}

void SdlEvents::OnMinimize() 
{
}

void SdlEvents::OnRestore() 
{
}

void SdlEvents::OnResize(int w,int h) 
{
}

void SdlEvents::OnExpose() 
{
}

void SdlEvents::OnExit() 
{
}

void SdlEvents::OnUser(Uint8 type, int code, void* data1, void* data2) 
{
}
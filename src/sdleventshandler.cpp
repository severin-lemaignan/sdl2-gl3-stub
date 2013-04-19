#include "sdleventshandler.h"


SDLEventsHandler::SDLEventsHandler() {
}

SDLEventsHandler::~SDLEventsHandler() {
    //Do nothing
}

void SDLEventsHandler::onEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_WINDOWEVENT: {
            switch(Event->window.event) {
                case SDL_WINDOWEVENT_ENTER: {
                    onMouseFocus();
                    break;
        }
                 case SDL_WINDOWEVENT_LEAVE: {
                    onMouseBlur();
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_GAINED: {
                    onInputFocus();
                    break;
                }
                 case SDL_WINDOWEVENT_FOCUS_LOST: {
                    onInputBlur();
                    break;
                }
                case SDL_WINDOWEVENT_RESTORED:    {
                    onRestore();
                    break;
                }
                 case SDL_WINDOWEVENT_MINIMIZED:    {
                    onMinimize();
                    break;
                }
            case SDL_WINDOWEVENT_RESIZED: {
                    onResize(Event->window.data1,Event->window.data2);
                    break;
            }
            case SDL_WINDOWEVENT_EXPOSED: {
                    onExpose();
                    break;
            }
            }
            break;
        }

        case SDL_KEYDOWN: {
            onKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_KEYUP: {
            onKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION: {
            onMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    onLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    onRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    onMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    onLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    onRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    onMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_JOYAXISMOTION: {
            onJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }

        case SDL_JOYBALLMOTION: {
            onJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }

        case SDL_JOYHATMOTION: {
            onJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            onJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }

        case SDL_JOYBUTTONUP: {
            onJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }

        case SDL_QUIT: {
            onExit();
            break;
        }

        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }

        default: {
            onUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}

void SDLEventsHandler::onInputFocus() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onInputBlur() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onKeyDown(SDL_Keycode sym, Uint16 mod, Uint32 unicode) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onKeyUp(SDL_Keycode sym, Uint16 mod, Uint32 unicode) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMouseFocus() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMouseBlur() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMouseWheel(bool Up, bool Down) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onJoyButtonDown(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onJoyButtonUp(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onMinimize() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onRestore() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onResize(int w,int h) {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onExpose() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onExit() {
    //Pure virtual, do nothing
}

void SDLEventsHandler::onUser(Uint8 type, int code, void* data1, void* data2) {
    //Pure virtual, do nothing
}

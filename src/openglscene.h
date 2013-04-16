#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "sdleventshandler.h"
#include "glrenderer.h"

class OpenGLScene : public SDLEventsHandler
{
    public:

    OpenGLScene(std::string title, int width, int height);
    ~OpenGLScene();

    bool init();
    void mainLoop();

    void onResize(int w, int h);
    void onExit();
    void onKeyDown(SDL_Keycode sym, SDL_Keymod mod, Uint16 unicode);

    private:

    bool running;

    std::string m_title;
    int m_width;
    int m_height;

    SDL_Window* m_window;
    SDL_GLContext m_context;

    GLRenderer renderer;
};


#endif // OPENGLSCENE_H

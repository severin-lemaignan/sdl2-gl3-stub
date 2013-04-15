#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H


// Includes
#ifdef GLEW

#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <string>


// Classe

class OpenGLScene
{
    public:

    OpenGLScene(std::string title, int width, int height);
    ~OpenGLScene();

    bool init();
    bool initGL();
    void mainLoop();


    private:

    std::string m_title;
    int m_width;
    int m_height;

    SDL_Window* m_window;
    SDL_GLContext m_context;
    SDL_Event m_events;
};


#endif // OPENGLSCENE_H

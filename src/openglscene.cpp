#include <iostream>

#include <glm/glm.hpp>
#include "openglscene.h"


using namespace std;
using namespace glm;

OpenGLScene::OpenGLScene(string title, int width, int height):m_title(title), m_width(width), m_height(height), renderer() {}

OpenGLScene::~OpenGLScene() {}

bool OpenGLScene::init()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_width, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_window == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_context = SDL_GL_CreateContext(m_window);

    if(m_context == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }

    renderer.load();

    renderer.camera.pose = vec3(0.0, 0.0, 10.0);
    renderer.camera.lookat = vec3(0.0, 0.0, 0.0);


    return true;
}

void OpenGLScene::onResize(int w, int h) {
    cout << w << ", " << h << endl;
    renderer.resize(w,h);
}
void OpenGLScene::onExit() {
    running = false;
}

void OpenGLScene::onKeyDown(SDL_Keycode sym, SDL_Keymod mod, Uint16 unicode) {

    switch(sym) {
    case SDLK_ESCAPE:
        running = false;
        break;
    case SDLK_UP:
        renderer.camera.moveLookAt(0.0, 0.1);
        break;
    case SDLK_DOWN:
        renderer.camera.moveLookAt(0.0, -0.1);
        break;

    }

}

void OpenGLScene::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
    float ratio = 100.0f;
    if (Left)
    {
    renderer.camera.moveLookAt(relX / ratio, relY / ratio);
    }
    if (Right)
    {
    renderer.camera.moveAt(relX / ratio, relY / ratio, 0.0);
    }
}


void OpenGLScene::mainLoop()
{

    running = true;

    while(running)
    {
        SDL_Event event;
        if(SDL_PollEvent(&event)) onEvent(&event);

        renderer.display();

        SDL_GL_SwapWindow(m_window);
    }
}


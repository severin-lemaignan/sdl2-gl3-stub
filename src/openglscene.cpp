#include "openglscene.h"

OpenGLScene::OpenGLScene(std::string title, int width, int height):m_title(title), m_width(width), m_height(height) {}

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

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_width, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

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

    return true;
}


bool OpenGLScene::initGL()
{
    #ifdef GLEW

        // On initialise GLEW

        GLenum initGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_context);
            SDL_DestroyWindow(m_window);
            SDL_Quit();

            return false;
        }

    #endif


    // Tout s'est bien passé, on retourne true

    return true;
}


void OpenGLScene::mainLoop()
{
    // Variables

    bool done(false);
    float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};

    // Boucle principale

    while(!done)
    {
        // Gestion des évènements

        SDL_WaitEvent(&m_events);

        if(m_events.window.event == SDL_WINDOWEVENT_CLOSE)
            done = 1;


        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT);


        // On remplie puis on active le tableau Vertex Attrib 0

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);


        // On affiche le triangle

        glDrawArrays(GL_TRIANGLES, 0, 3);


        // On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin

        glDisableVertexAttribArray(0);


        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(m_window);
    }
}


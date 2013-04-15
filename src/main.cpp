#include <iostream>

#include "openglscene.h"


using namespace std;

int main(int argc, char **argv)
{
    // Création de la sène

    OpenGLScene scene("Test", 800, 600);


    // Initialisation de la scène

    if(!scene.init()) return -1;



    // Boucle Principale

    scene.mainLoop();


    // Fin du programme


}


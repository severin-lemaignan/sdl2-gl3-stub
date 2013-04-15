// ---------------------------------------------------------------------------
// LoadShader.cpp
// Quick and dirty LoadShader function for the OpenGL Programming Guide 4.3
// Red Book.
//
// Author: Qoheleth
// http://www.opengl.org/discussion_boards/showthread.php/180175-Redbook-8th-sample-code?p=1245842#post1245842
// ---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


#include "loadshaders.h"
 
GLuint LoadShaders( ShaderInfo shaderInfo )
{
    GLuint logLength;

    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;
    vertexShader   = glCreateShader( GL_VERTEX_SHADER );    // create a vertex shader object
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );  // create a fragment shader object
 
    // load and compile vertex shader
    string shaderProgramText;
    const char* text = getShaderProgram( shaderInfo.vShaderFile, shaderProgramText );
    glShaderSource( vertexShader, 1, &text, NULL );
    glCompileShader( vertexShader );

    GLint status;


    // Check vertex shader
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);



    if ( !( status == GL_TRUE ) )
        cerr << "\nVertex Shader compilation failed..." << '\n';

    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertexShaderError(logLength);
    glGetShaderInfoLog(vertexShader, logLength, NULL, &vertexShaderError[0]);
    std::cout << &vertexShaderError[0] << std::endl;


    // load and compile fragment shader
    shaderProgramText = "";
    text = getShaderProgram( shaderInfo.fShaderFile, shaderProgramText );
    glShaderSource( fragmentShader, 1, &text, NULL );
    glCompileShader( fragmentShader );
 
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &status );
 
    if ( !( status == GL_TRUE ) )
        cerr << "\nFragment Shader compilation failed..." << '\n';

    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragmentShaderError(logLength);
    glGetShaderInfoLog(fragmentShader, logLength, NULL, &fragmentShaderError[0]);
    std::cout << &fragmentShaderError[0] << std::endl;


    // create the shader program
    program = glCreateProgram();
 
    // attach the vertex and fragment shaders to the program
    glAttachShader( program, vertexShader );
    glAttachShader( program, fragmentShader );
 
    // link the objects for an executable program
    glLinkProgram( program );
 
    glGetProgramiv( program, GL_LINK_STATUS, &status );
    if ( !( status == GL_TRUE ) )
        cout << "Link failed..." << endl;
 
    // return the program
    return program;
}
 
const char* getShaderProgram( const char *filePath, string &shader )
{
    fstream shaderFile( filePath, ios::in );
 
    if ( shaderFile.is_open() )
    {
        std::stringstream buffer;
        buffer << shaderFile.rdbuf();
        shader = buffer.str();
        buffer.clear();
    }
    shaderFile.close();
 
    return shader.c_str();
}

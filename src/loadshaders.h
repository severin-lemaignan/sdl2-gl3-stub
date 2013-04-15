#pragma once
// ---------------------------------------------------------------------------
// LoadShader.h
// Quick and dirty LoadShader function for the OpenGL Programming Guide 4.3
// Red Book.
//
// Author: Qoheleth
// [url]http://www.opengl.org/discussion_boards/showthread.php/180175-Redbook-8th-sample-code?p=1245842#post1245842[/url]
// ---------------------------------------------------------------------------

#include <string>

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

struct ShaderInfo {
    GLenum vTarget;
    const char *vShaderFile;
    GLenum fTarget;
    const char *fShaderFile;
};
 
GLuint LoadShaders( ShaderInfo shaderInfo );
const char* getShaderProgram( const char *filePath, std::string &shaderProgramText );

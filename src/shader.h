#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>

#include <glm/glm.hpp>

// Stolen from http://www.swiftless.com/tutorials/opengl4/2-opengl-shaders.html

/**
	Shader is a class designed to allow us to load and use a GLSL shader program in
	our OpenGL application. It allows us to provide filenames for the vertex and 
	fragment shaders, and then creates the shader. It also lets us bind and 
	unbind the GLSL shader program as required.
*/
class Shader {
public:
    Shader(); // Default constructor
    Shader(const char *vsFile, const char *fsFile); // Constructor for creating a shader from two shader filenames
    ~Shader(); // Deconstructor for cleaning up
    
    void init(const std::string& vsFile, const std::string& fsFile); // Initialize our shader file if we have to
    
    void bind(); // Bind our GLSL shader program
    void unbind(); // Unbind our GLSL shader program
    
    unsigned int id(); // Get the identifier for our program

    // Returns a GLSL attribute location, using memoization to limit opengl calls to the minimum
    GLuint getAttrib(const std::string& attrib) const;

    void setUniform(const std::string& uniform, float x);
    void setUniform(const std::string& uniform, float x, float y);
    void setUniform(const std::string& uniform, float x, float y, float z);
    void setUniform(const std::string& uniform, float x, float y, float z, float w);
    void setUniform(const std::string& uniform, const glm::vec2& vec);
    void setUniform(const std::string& uniform, const glm::vec3& vec);
    void setUniform(const std::string& uniform, const glm::vec4& vec);
    void setUniform(const std::string& uniform, const glm::mat4& mat);

    // Returns a uniform location, using memoization to limit opengl calls to the minimum
    GLuint getUniform(const std::string& uniform) const;


private:

    mutable std::map<std::string, GLuint> _uniforms;
    mutable std::map<std::string, GLuint> _attribs;

    unsigned int shader_id; // The shader program identifier
    unsigned int shader_vp; // The vertex shader identifier
    unsigned int shader_fp; // The fragment shader identifier

    bool inited; // Whether or not we have initialized the shader
};

#endif //SHADER_H

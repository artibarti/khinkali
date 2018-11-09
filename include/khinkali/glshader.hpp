#ifndef GL_SHADER_H
#define GL_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "utils/gltypes.hpp"
#include "utils/glutils.hpp"

namespace khinkali
{

    enum GLShaderType 
    { 
        GL_SHADER_TYPE_VERTEX, 
        GL_SHADER_TYPE_FRAGMENT 
    };    

    class GLShader
    {
        public:
            GLShader();
            GLShader(std::string filename_, GLint type_);

            GLuint& getShader();
            std::string getFilename();
            int getShaderType();
            std::string getShaderCode();

        private:
            void compileShader();
            void loadShaderCode();

            std::string filename;
            GLint type;
            std::string shader_code;
            GLuint shader = 0;

            GLchar compileLogBuffer[4098];

    };

    GLShader::GLShader()
    {

    }

    GLShader::GLShader(std::string filename_, GLint type_)
    {
        filename = filename_;
        type = type_;

        loadShaderCode();
        compileShader();
    }
    
    GLuint& GLShader::getShader()
    {
        return shader;
    }

    std::string GLShader::getFilename()
    {
        return filename;
    }

    int GLShader::getShaderType()
    {
        return type;
    }
    
    std::string GLShader::getShaderCode()
    {
        return shader_code;
    }

    void GLShader::loadShaderCode()
    {
        shader_code = loadShaderFromFile(filename);
    }

    void GLShader::compileShader()
    {
        shader =  glCreateShader(type);
        const GLchar* shader_code_ptr[] = { shader_code.c_str() };
        glShaderSource(shader, 1, shader_code_ptr, NULL);
        glCompileShader(shader);

        GLint status;
	    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	    if (status == GL_FALSE)
	    {
		    glGetShaderInfoLog(shader, sizeof(compileLogBuffer) / sizeof(GLchar), NULL, compileLogBuffer);
            llog("Error occured during the compilation of shader: " + filename);
            llog(compileLogBuffer);
            memset(compileLogBuffer, 0, sizeof compileLogBuffer);
            throw glShaderCompileException();
	    }
    }
}

#endif
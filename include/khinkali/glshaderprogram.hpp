#ifndef GL_SHADERPROGRAM_HPP
#define GL_SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include "utils/gltypes.hpp"
#include "glshader.hpp"
#include "utils/gllog.hpp"

namespace khinkali
{
    class GLShaderProgram
    {
        public:
            GLShaderProgram();
            ~GLShaderProgram();
            GLuint& getProgram();
            void attachShader(int pos, std::string filename, GLint type);            

        private:

            GLuint program;
            std::map<uint, GLShader> vertex_shaders;
            std::map<uint, GLShader> fragment_shaders;
            GLchar buffer[4098];            
    };

    GLShaderProgram::GLShaderProgram()
    {
        program = glCreateProgram();
    }

    GLShaderProgram::~GLShaderProgram()
    {
        glDeleteProgram(program);
    }

    GLuint& GLShaderProgram::getProgram()
    {
        for (auto shader : vertex_shaders)
        {
            glAttachShader(program, shader.second.getShader());
        }
        for (auto shader : fragment_shaders)
        {
            glAttachShader(program, shader.second.getShader());            
        }
        glLinkProgram(program);

	    GLint status;    
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
	    {
		    glGetProgramInfoLog(program, sizeof(buffer) / sizeof(GLchar), NULL, buffer);
		    llog("Error while linking shader program");
            llog(buffer);
            memset(buffer, 0, sizeof buffer);
	    }


        return program;
    }

    void GLShaderProgram::attachShader(int pos, std::string filename, GLint type)
    {
        GLShader shader(filename, type);
        if (type == GL_VERTEX_SHADER)
        {
            vertex_shaders[pos] = shader;
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            fragment_shaders[pos] = shader;
        }
    }
}

#endif
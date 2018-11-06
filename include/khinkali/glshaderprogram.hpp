#ifndef GL_SHADERPROGRAM_HPP
#define GL_SHADERPROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include "utils/gltypes.hpp"
#include "glshader.hpp"

namespace khinkali
{
    class GLShaderProgram
    {
        public:
            GLShaderProgram();
            GLuint& getProgram();
            void attachShader(int pos, std::string filename, GLint type);            

        private:

            GLuint program;
            std::map<uint, GLShader> vertex_shaders;
            std::map<uint, GLShader> fragment_shaders;
    };

    GLShaderProgram::GLShaderProgram()
    {
        program = glCreateProgram();
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
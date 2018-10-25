#ifndef GL_SHAPE_H
#define GL_SHAPE_H

#include "gltypes.hpp"
#include <glm/vec2.hpp>
#include <vector>
#include "glconsts.hpp"
#include "glutils.hpp"
#include "gllog.hpp"
#include <algorithm>

namespace Lanuka
{
    class GLShape 
    {
        public:

            ~GLShape();
            std::vector<glm::vec3>& getVertives();
            std::vector<glm::vec3>& getColors();
            void draw();
            void attachShader(GLuint& shader);
            void setVertices(std::initializer_list<glm::vec3> il);
            void setColors(std::initializer_list<glm::vec3> il);
            void setIndices(std::initializer_list<glm::vec3> il);

        protected:

            void initBuffers();
            void clearBuffers();

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;
            std::vector<glm::vec3> indices;
            std::vector<std::string> shaders;

            GLuint vertex_buffer = 0, color_buffer = 0;
            GLuint vertex_array = 0;
            GLuint program = 0;

            int draw_mode;
    };

    GLShape::~GLShape()
    {
        vertices.clear();
        colors.clear();
        indices.clear();
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteBuffers(1, &color_buffer);
    }

    void GLShape::initBuffers()
    {        
        glGenBuffers(1, &vertex_buffer);
        glGenBuffers(1, &color_buffer);
        glGenVertexArrays(1, &vertex_array);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(vertex_array);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void GLShape::clearBuffers()
    {

    }

    void GLShape::draw()
    {
        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(draw_mode, 0,3);
        glBindVertexArray(0);
    }

    void GLShape::attachShader(GLuint& shader)
    {
        glAttachShader(program, shader);
        glLinkProgram(program);
        glDeleteShader(shader);      
    }

    void GLShape::setVertices(std::initializer_list<glm::vec3> il)
    {
        vertices = il;
        initBuffers();   
    }

    void GLShape::setColors(std::initializer_list<glm::vec3> il)
    {
        colors = il;
        initBuffers();   
    }

    void GLShape::setIndices(std::initializer_list<glm::vec3> il)
    {
        indices = il;
        initBuffers();   
    }

}

#endif
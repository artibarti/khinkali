#ifndef GL_DRAWABLE_H
#define GL_DRAWABLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../utils/gltypes.hpp"
#include <glm/vec2.hpp>
#include <vector>
#include "../utils/glconsts.hpp"
#include "../utils/glutils.hpp"
#include "../utils/gllog.hpp"
#include <algorithm>

namespace Lanuka
{
    class GLDrawable
    {
        public:
            void draw();
            void setColor(double r, double g, double b);
            void setColor(glm::vec3 color);
            void attachShader(GLuint& shader);


        protected:

            void callMeBeforeAnythingInMyDerivedClasses();

            // buffer initialization
            void initVertexBuffer();
            void initColorBuffer();
            void initIndexBuffer();

            void deleteBuffers();

            // vectors
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;
            std::vector<GLuint> indices;
            std::vector<std::string> shaders;
            
            // opengl objects
            GLuint vertex_buffer = 0, color_buffer = 0, index_buffer = 0;
            GLuint vertex_array = 0;
            GLuint program = 0; 

            // non-user related info variables
            GLDrawableType drawable_type;
            int draw_mode;
           
    };

    void GLDrawable::setColor(glm::vec3 color)
    {
        colors.clear();
        for (int i = 0; i<vertexNumberConstraintForDrawables[drawable_type]; i++)
            colors.push_back(color);

        initColorBuffer();
    }

    void GLDrawable::setColor(double r, double g, double b)
    {
        colors.clear();
        for (int i = 0; i<vertexNumberConstraintForDrawables[drawable_type]; i++)
            colors.push_back(glm::vec3(r,g,b));

        initColorBuffer();
    }

    void GLDrawable::initVertexBuffer()
    {
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLDrawable::initColorBuffer()
    {
        glGenBuffers(1, &color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);        
    }

    void GLDrawable::initIndexBuffer()
    {
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);        
    }

    void GLDrawable::callMeBeforeAnythingInMyDerivedClasses()
    {
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);
        program = glCreateProgram();  
    }

    void GLDrawable::draw()
    {
        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void GLDrawable::deleteBuffers()
    {
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteBuffers(1, &color_buffer);
    }

    void GLDrawable::attachShader(GLuint& shader)
    {
        glAttachShader(program, shader);
        glLinkProgram(program);
        glDeleteShader(shader);      
    }

}

#endif
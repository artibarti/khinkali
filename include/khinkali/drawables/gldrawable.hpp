#ifndef GL_DRAWABLE_H
#define GL_DRAWABLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/stb_image.h"
#include "../utils/gltypes.hpp"
#include <glm/vec2.hpp>
#include <vector>
#include "../utils/glconsts.hpp"
#include "../utils/glutils.hpp"
#include "../utils/gllog.hpp"
#include <algorithm>
#include "../glshader.hpp"
#include "../glshaderprogram.hpp"

namespace khinkali
{
    class GLDrawable
    {
        public:
            void draw();
            void setColor(double r, double g, double b);
            void setColor(glm::vec3 color);
            void attachProgram(GLShaderProgram *program_);

        protected:

            // buffer initialization
            void initVertexBuffer();
            void initColorBuffer();
            void initIndexBuffer();
            void initNormalBuffer();
            void initUVbuffer();

            // texture
            void initTexture();

            // vectors
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;
            std::vector<glm::vec3> normals;
            std::vector<GLuint> indices;
            std::vector<glm::vec2> UVcoords;
            
            // buffer objects and shader program
            GLuint vertex_buffer, color_buffer, index_buffer, normal_buffer, uv_buffer;
            GLuint vertex_array = 0;
            GLuint texture;
            GLuint* program; 

            // non user-related info variables
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
        
        glEnableVertexAttribArray(VERTEX_ATTRIB_POS);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(VERTEX_ATTRIB_POS,3,GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLDrawable::initColorBuffer()
    {
        glGenBuffers(1, &color_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(VERTEX_ATTRIB_COLOR);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(VERTEX_ATTRIB_COLOR,3, GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);        
    }

    void GLDrawable::initNormalBuffer()
    {
        glGenBuffers(1, &normal_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
        glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLDrawable::initUVbuffer()
    {
        glGenBuffers(1, &uv_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glBufferData(GL_ARRAY_BUFFER, UVcoords.size() * sizeof(glm::vec2), UVcoords.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(VERTEX_ATTRIB_UV);
	    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	    glVertexAttribPointer(VERTEX_ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, 0, 0);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLDrawable::initIndexBuffer()
    {
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);        
    }

    void GLDrawable::initTexture()
    {
	    int x, y, n;
	    auto image = stbi_load("bricks.jpg", &x, &y, &n, 4);

	    GLfloat maxAnisotropy;
	    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);

        glGenTextures(1, &texture);
	    glBindTexture(GL_TEXTURE_2D, texture);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
	    glGenerateMipmap(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(image);
    }

    void GLDrawable::draw()
    {
    	glActiveTexture(GL_TEXTURE0);    
    	glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(*program);
        glBindVertexArray(vertex_array);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void GLDrawable::attachProgram(GLShaderProgram *program_)
    {
        program = &(program_ -> getProgram());
    }
    
}

#endif
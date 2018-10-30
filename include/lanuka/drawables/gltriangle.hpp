#ifndef GL_TRIANGLE_H
#define GL_TRIANGLE_H

#include <GL/glew.h>
#include "glshape.hpp"
#include <vector>
#include <string>
#include "../utils/glutils.hpp"
#include <iostream>

namespace Lanuka
{
    class GLTriangle : public GLShape
    {
        public:
            GLTriangle();
            GLTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);
    };

    GLTriangle::GLTriangle()
    {        
        draw_mode = GL_TRIANGLES;
        program = glCreateProgram();  
    }

    GLTriangle::GLTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
    {
        callMeBeforeAnythingInMyDerivedClasses();

        draw_mode = GL_TRIANGLES;
        drawable_type = GL_DRAWABLE_TYPE_TRIANGLE;

        vertices.push_back(glm::vec3(v1,0));
        vertices.push_back(glm::vec3(v2,0));
        vertices.push_back(glm::vec3(v3,0));
        initVertexBuffer();

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        initIndexBuffer();

    }
}

#endif
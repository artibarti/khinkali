#ifndef GL_TRIANGLE_H
#define GL_TRIANGLE_H

#include <GL/glew.h>
#include "glshape.hpp"
#include <vector>
#include <string>
#include "glutils.hpp"

namespace Lanuka
{
    class GLTriangle : public GLShape
    {
        public:
            GLTriangle();

    };

    GLTriangle::GLTriangle()
    {        
        vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
	    vertices.push_back(glm::vec3( 0.5f, -0.5f, 0.0f));
	    vertices.push_back(glm::vec3( 0.0f,  0.5f, 0.0f));
        colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f));
	    colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f));
	    colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));

        draw_mode = GL_TRIANGLES;
        initBuffers();      
        addShader(GL_SHADER_TYPE_VERTEX, "shaders/first.vs");        
        //addShader(GL_SHADER_TYPE_FRAGMENT, "shaders/first.fs");
        attachShaders();
  
    }
}

#endif
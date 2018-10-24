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
        draw_mode = GL_TRIANGLES;
        init();        
    }
}

#endif
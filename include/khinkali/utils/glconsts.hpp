#ifndef GL_CONSTS_H
#define GL_CONSTS_H

#include <glm/vec3.hpp>
#include <map>
#include "gltypes.hpp"

namespace khinkali
{
    const glm::vec3 GL_COLOR_RED = {1.0, 0.0, 0.0};
    const glm::vec3 GL_COLOR_BLUE = {0.0, 0.0, 1.0};
    const glm::vec3 GL_COLOR_GREEN = {0.0, 1.0, 0.0};
    const glm::vec3 GL_COLOR_BLACK = {0.0, 0.0, 0.0};
    const glm::vec3 GL_COLOR_WHITE = {1.0, 1.0, 1.0};
    const glm::vec3 GL_COLOR_ORANGE = {0.9, 0.5, 0.0};
    const glm::vec3 GL_COLOR_GREY = {0.5, 0.5, 0.5};
    const glm::vec3 GL_COLOR_LIGHTBLUE = {0.2, 0.3, 1.0};

    std::map<GLDrawableType, int> vertexNumberConstraintForDrawables =
    {
        {GL_DRAWABLE_TYPE_TRIANGLE, 3},
        {GL_DRAWABLE_TYPE_RECTANGLE, 4},
        {GL_DRAWABLE_TYPE_CUBE, 24}
    };

    const int UNIFORM_MODELVIEWPROJECTION = 0;
    const int UNIFORM_NORMAL = 1;
    
    const int VERTEX_ATTRIB_POS = 0;
    const int VERTEX_ATTRIB_UV = 1;
    const int VERTEX_ATTRIB_NORMAL = 2;
    const int VERTEX_ATTRIB_COLOR = 3;

};



#endif
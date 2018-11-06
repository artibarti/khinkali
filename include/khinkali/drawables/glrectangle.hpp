#ifndef GL_RECTAGLE_H
#define GL_RECTAGLE_H

#include "gldrawable.hpp"

namespace khinkali
{

    class GLRectangle : public GLDrawable
    {
        public:
            GLRectangle();
            GLRectangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec2 v4);
    };

    GLRectangle::GLRectangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec2 v4)
    {
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        draw_mode = GL_TRIANGLES;
        drawable_type = GL_DRAWABLE_TYPE_RECTANGLE;

        vertices.push_back(glm::vec3(v1,0));
        vertices.push_back(glm::vec3(v2,0));
        vertices.push_back(glm::vec3(v3,0));
        vertices.push_back(glm::vec3(v4,0));
        initVertexBuffer();

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(3);
        indices.push_back(1);
        indices.push_back(2);
        initIndexBuffer();
    }
}

#endif
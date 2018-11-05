#ifndef GL_CUBE_HPP
#define GL_CUBE_HPP

#include "gldrawable.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace khinkali
{
    class GLCube : public GLDrawable
    {
        public: 
            GLCube();
            GLCube(glm::vec3 center, double size);    
    };

    GLCube::GLCube(glm::vec3 center, double size)
    {
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);
        program = glCreateProgram(); 

        draw_mode = GL_TRIANGLES;
        drawable_type = GL_DRAWABLE_TYPE_CUBE;

        vertices = 
        {
	        glm::vec3(center[0] - size/2, center[1] - size/2,  center[2] + size/2),
	        glm::vec3(center[0] + size/2, center[1] - size/2,  center[2] + size/2),
	        glm::vec3(center[0] - size/2, center[1] - size/2,  center[2] - size/2),
	        glm::vec3(center[0] + size/2, center[1] - size/2,  center[2] - size/2),
	        glm::vec3(center[0] - size/2, center[1] + size/2,  center[2] + size/2),
	        glm::vec3(center[0] + size/2, center[1] + size/2,  center[2] + size/2),
	        glm::vec3(center[0] - size/2, center[1] + size/2,  center[2] - size/2),
	        glm::vec3(center[0] + size/2, center[1] + size/2,  center[2] - size/2)
        };
        initVertexBuffer();

        indices =
        {
        	// front
        	0, 1, 4,
        	4, 1, 5,
        	// right
        	5, 1, 7,
        	7, 1, 3, 
        	// back
        	3, 2, 7,
        	7, 2, 6, 
        	// left
        	2, 4, 6,
        	4, 2, 0, 
        	// bottom
        	2, 1, 0,
        	1, 2, 3, 
        	// top
        	6, 4, 7,
        	7, 4, 5, 
        };
        initIndexBuffer();

        std::vector<glm::vec3> facenormals =
        {
        	glm::vec3( 0.0f, 0.0f, 1.0f),
        	glm::vec3( 1.0f, 0.0f, 0.0f),
        	glm::vec3( 0.0f, 0.0f,-1.0f),
        	glm::vec3(-1.0f, 0.0f, 0.0f),
        	glm::vec3( 0.0f,-1.0f, 0.0f),
        	glm::vec3( 0.0f, 1.0f, 0.0f),
        };

        std::vector<glm::vec3> tmp_normals(vertices.size(), glm::vec3(0.0f));
	    std::vector<int> counts(vertices.size(), 0);

        for (int i = 0; i < indices.size(); i++)
	    {
    		unsigned int faceIndex = i/6;
			tmp_normals[indices[i]] += facenormals[faceIndex];
			counts[indices[i]]++;
        }

        for (int i = 0; i < vertices.size(); i++)
		    tmp_normals[i] = glm::normalize(tmp_normals[i] / GLfloat(counts[i]));

        for (int i = 0; i < tmp_normals.size(); i++)
            normals.push_back(tmp_normals[i]);

        initNormalBuffer();

	}

}

#endif
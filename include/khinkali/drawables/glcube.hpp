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

        draw_mode = GL_TRIANGLES;
        drawable_type = GL_DRAWABLE_TYPE_CUBE;

        std::vector<glm::vec3> tmp_vertices = 
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

		std::vector<glm::vec3> tmp_normals=
		{
			glm::vec3(-0.33f, -0.33f,  0.33f),
			glm::vec3( 0.33f, -0.33f,  0.33f),
			glm::vec3(-0.33f, -0.33f, -0.33f),
			glm::vec3( 0.33f, -0.33f, -0.33f),

			glm::vec3(-0.33f,  0.33f,  0.33f),
			glm::vec3( 0.33f,  0.33f,  0.33f),
			glm::vec3(-0.33f,  0.33f, -0.33f),
			glm::vec3( 0.33f,  0.33f, -0.33f),
		};

		std::vector<glm::vec2> tmp_UVcoords = 
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
		};

		std::vector<int> tmp_indices = 
		{
			// front
			0, 1, 4, 5,
			// right
			1, 3, 5, 7,
			// back
			3, 2, 7, 6,
			// left
			2, 0, 6, 4,
			// bottom
			2, 3, 0, 1,
			// top
			4, 5, 6, 7
		};

		std::vector<GLuint> faceIndices=
		{
			0, 1, 2,
			2, 1, 3
		};

		for (size_t i = 0; i < tmp_indices.size(); ++i)
		{
			vertices.push_back(tmp_vertices[tmp_indices[i]]);
			normals.push_back(tmp_normals[tmp_indices[i]]);
			UVcoords.push_back(tmp_UVcoords[i%4]);
		}

		for (int i = 0; i < 6; i++)
			for (size_t j = 0; j < faceIndices.size(); ++j)
				indices.push_back(faceIndices[j] + i * 4);

		initVertexBuffer();
		initUVbuffer();
		initNormalBuffer();
		initIndices();
	}

}

#endif
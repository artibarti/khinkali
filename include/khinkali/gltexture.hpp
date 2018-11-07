#ifndef GL_TEXTURE_HPP
#define GL_TEXTURE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "utils/gllog.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb_image.h"

namespace khinkali
{
    class GLTexture
    {
        public:
            GLTexture(const char* filename);
            ~GLTexture();
            void activate();

        private:
            GLuint texture;
    };

    GLTexture::~GLTexture()
    {
        glDeleteTextures(1, &texture);
    }

    GLTexture::GLTexture(const char* filename)
    {
        int x, y, n;
	    auto image = stbi_load(filename, &x, &y, &n, 4);

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

    void GLTexture::activate()
    {
        glActiveTexture(GL_TEXTURE0);    
    	glBindTexture(GL_TEXTURE_2D, texture);
    }
}

#endif
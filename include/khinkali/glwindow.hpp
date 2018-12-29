#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <functional>
#include "utils/gllog.hpp"

namespace khinkali
{
 
    class GLWindow
    {
        public:
            GLWindow() {};
            GLWindow(int width, int height, const char* title);
            GLFWwindow* getWindow();
            void destroy();

        private:
            GLFWwindow* window;
            int window_width;
            int window_height;
            bool resizeable = false;
            std::string window_title;

    };

    GLWindow::GLWindow(int width, int height, const char* title)
    {
        if (!glfwInit())
            return;

        window_width = width;
        window_height = height;
        window_title = title;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;

        }

	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwMakeContextCurrent(window);
    	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    GLFWwindow* GLWindow::getWindow()
    {
        return window;
    }

    void GLWindow::destroy()
    {
        glfwDestroyWindow(window);
    }
}

#endif
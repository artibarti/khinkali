#ifndef GL_WINDOW_HPP
#define GL_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

namespace khinkali
{
    class GLWindow
    {
        public:
            GLWindow(int width, int height, const char* title = "Unnamed window");
            GLFWwindow* getWindow();

            void setKeyCallbackFunction(void (*keyCallback_)(int, int, int, int));
            void setMouseCallbackFunction(void (*mouseCallback_)(GLdouble, GLdouble));

        private:
            GLFWwindow* window;
            int window_width;
            int window_height;
            bool resizeable = false;
            std::string window_title;

            static void keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods);
            static void mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y);
            void (*keyCallback)(int, int, int, int);
            void (*mouseCallback)(GLdouble, GLdouble);

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

        glfwSetWindowUserPointer(window, this);

	    glfwSetKeyCallback(window, keyPressedEventCatcher);
	    glfwSetCursorPosCallback(window, mouseMovedEventCatcher);
    	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    GLFWwindow* GLWindow::getWindow()
    {
        return window;
    }

    void GLWindow::keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods)
    {
        GLWindow* w = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
        w -> keyCallback(key, scancode, actions, mods);
        glfwPollEvents();
    }

    void GLWindow::mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y)
    {
        GLWindow* w = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
        w -> mouseCallback(x,y) ;
        glfwPollEvents();
    }

    void GLWindow::setKeyCallbackFunction(void (*keyCallback_)(int, int, int, int))
    {
        keyCallback = keyCallback_;
    }

    void GLWindow::setMouseCallbackFunction(void (*mouseCallback_)(GLdouble, GLdouble))
    {
        mouseCallback = mouseCallback_;
    }

}

#endif
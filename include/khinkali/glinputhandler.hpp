#ifndef GL_INPUT_HANDLER_H
#define GL_INPUT_HANDLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glwindow.hpp"

namespace khinkali
{    
    class KeyEvent
    {   
        public:
            int key = 0;
            int scancode = 0;
            int actions = 0;
            int mods = 0;
    };

    class MouseEvent
    {
        public:
            double x = -1;
            double y = -1;
    };


    class GLInputHandler
    {
        public:
            GLInputHandler();
            
            void setWindow(GLWindow* win);
            void pushMouseEvent(int key, int scancode, int action, int mods);
            void pushKeyEvent(double x, double y);
            MouseEvent getMouseEvent();
            KeyEvent getKeyEvent();
            bool isThereAnyKeyboardInputToHandle();
            bool isThereAnyMouseInputToHandle();

        private:
            
            MouseEvent mouseEvent;
            KeyEvent keyEvent;
            GLWindow* window;
            bool activeMouseEvent = false;
            bool activeKeyboardEvent = false;

            static void keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods);    
            static void mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y);
    };

    GLInputHandler::GLInputHandler()
    {
        std::cout << "Empty constructor called" << std::endl;
    }

    void GLInputHandler::setWindow(GLWindow* win)
    {
        window = win;
        glfwSetWindowUserPointer(window -> getWindow(), this);
	    glfwSetKeyCallback(window -> getWindow(), keyPressedEventCatcher);
	    glfwSetCursorPosCallback(window -> getWindow(), mouseMovedEventCatcher);
    }

    void GLInputHandler::keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods)
    {
        GLInputHandler* inputHandler 
            = static_cast<GLInputHandler*>(glfwGetWindowUserPointer(window));
        
        inputHandler -> keyEvent.key = key;
        inputHandler -> keyEvent.scancode = scancode;
        inputHandler -> keyEvent.actions = actions;
        inputHandler -> keyEvent.mods = mods;
        inputHandler -> activeKeyboardEvent = true;
    }

    void GLInputHandler::mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y)
    {
        GLInputHandler* inputHandler 
            = static_cast<GLInputHandler*>(glfwGetWindowUserPointer(window));
        
        inputHandler -> mouseEvent.x = x;
        inputHandler -> mouseEvent.y = y;
        inputHandler -> activeMouseEvent = true;
    }

    bool GLInputHandler::isThereAnyKeyboardInputToHandle()
    {
        if (activeKeyboardEvent)
        {
            activeKeyboardEvent = false;
            return true;
        }
        else
            return false;
    }

    bool GLInputHandler::isThereAnyMouseInputToHandle()
    {
        if (activeMouseEvent)
        {
            activeMouseEvent = false;
            return true;
        }
        else
            return false;
    }

};

#endif
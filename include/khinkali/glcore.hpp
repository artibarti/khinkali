
#ifndef GL_CORE_H
#define GL_CORE_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include "utils/glexcepion.hpp"
#include "glscene.hpp"
#include "glwindow.hpp"

namespace khinkali
{
    class GLCore
    {
        public:
            GLCore(int win_width, int win_height, const char* win_name);
            
            void start();
            void terminate();
            void attachScene(int pos, GLScene* scene);
            void detachScene(int pos);
            void showInfo();
        
            void keyPressedEventBroadcaster(int key, int scancode, int actions, int mods);
            void mouseMovedEventBroadcaster(GLdouble x, GLdouble y);

        private:
            GLWindow window;
            std::map<int, GLScene*> scenes;
            std::string window_name = "Unnamed window";
            int window_width = 0;
            int window_height = 0;

            static void keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods);
            static void mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y);

    };

    GLCore::GLCore(int win_width, int win_height, const char* win_name)
    {
        if (!glfwInit())
            return;

        window = GLWindow(win_width, win_height, win_name);
        
        glfwSetWindowUserPointer(window.getWindow(), this);
	    glfwSetKeyCallback(window.getWindow(), keyPressedEventCatcher);
	    glfwSetCursorPosCallback(window.getWindow(), mouseMovedEventCatcher);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
                return;
        }

        glEnable(GL_CULL_FACE);
	    glEnable(GL_DEPTH_TEST);        
    }

    void GLCore::start()
    {
        while (true)	
        {                
            glfwPollEvents();

            for (auto scene : scenes)
                scene.second -> draw();

            glfwSwapBuffers(window.getWindow());

            if (glfwWindowShouldClose( window.getWindow() ))
            {
                terminate();
                break;
            }
        }
    }

    void GLCore::terminate()
    {
        window.destroy();
        glfwTerminate();
    }

    void GLCore::attachScene(int pos, GLScene* scene)
    {
        scenes[pos] = scene;
    }

    void GLCore::detachScene(int pos)
    {
        scenes.erase(scenes.find(pos));
    }
  
    void GLCore::showInfo()
    {
        std::cout << "GLCore object with " << scenes.size() << " scenes" << std::endl;
        std::cout << std::endl;
    }

    void GLCore::keyPressedEventBroadcaster(GLint key, GLint scanCode, GLint action, GLint mods)
    {
        
        if ( key == GLFW_KEY_ESCAPE )
            glfwSetWindowShouldClose(window.getWindow(), true);

        for (auto scene : scenes)
            scene.second -> keyPressed(key, scanCode, action, mods);
    }

    void GLCore::mouseMovedEventBroadcaster(GLdouble x, GLdouble y)
    {
        for (auto scene : scenes)
            scene.second -> mouseMoved(x,y);
    }

    void GLCore::keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods)
    {
        GLCore* core = static_cast<GLCore*>(glfwGetWindowUserPointer(window));
        core -> keyPressedEventBroadcaster(key, scancode, actions, mods);
    }

    void GLCore::mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y)
    {
        GLCore* core = static_cast<GLCore*>(glfwGetWindowUserPointer(window));
        core -> mouseMovedEventBroadcaster(x,y) ;
    }

};

#endif

#ifndef GL_CORE2D_H
#define GL_CORE2D_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <map>
#include "glscene.hpp"
#include "utils/glexcepion.hpp"
#include <thread>
#include "glscene.hpp"

namespace khinkali
{

    class GLCore
    {
        public:
            GLCore(int win_width, int win_height, const char* win_name = NULL);
            void start();
            void terminate();
            void attachScene(int pos, GLScene* scene);
            void detachScene(int pos);
            void showInfo();
        
        private:
            GLFWwindow* window;
            std::map<int, GLScene*> scenes;
            std::string window_name = "Unnamed window";
            int window_width = 0;
            int window_height = 0;

            static void keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods);
            static void mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y);

            void keyPressed(GLint key, GLint scanCode, GLint action, GLint mods);
            void mouseMoved(GLdouble x, GLdouble y);
    };

    GLCore::GLCore(int win_width, int win_height, const char* win_name)
    {
        if (!glfwInit())
            return;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window_name = win_name;

        window = glfwCreateWindow(640, 480, win_name, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
                return;
        }

        glfwMakeContextCurrent(window);

        window_width = win_width;
        window_height = win_height;
        window_name = win_name;

	    glfwSetWindowUserPointer(window, this);

	    glfwSetKeyCallback(window, keyPressedEventCatcher);
	    glfwSetCursorPosCallback(window, mouseMovedEventCatcher);
    	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void GLCore::start()
    {
        while (!glfwWindowShouldClose(window))	
        {
            glfwPollEvents();

            for (auto scene : scenes)
                scene.second -> draw();

            glfwSwapBuffers(window);
        }
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

    void GLCore::keyPressed(GLint key, GLint scanCode, GLint action, GLint mods)
    {
        for (auto scene : scenes)
            scene.second -> keyPressed(key, scanCode, action, mods);
    }

    void GLCore::mouseMoved(GLdouble x, GLdouble y)
    {
        for (auto scene : scenes)
            scene.second -> mouseMoved(x,y);
    }

    void GLCore::keyPressedEventCatcher(GLFWwindow* window, int key, int scancode, int actions, int mods)
    {
        GLCore* core = static_cast<GLCore*>(glfwGetWindowUserPointer(window));
        core -> keyPressed(key, scancode, actions, mods);
        glfwPollEvents();
    }

    void GLCore::mouseMovedEventCatcher(GLFWwindow* window, GLdouble x, GLdouble y)
    {
        GLCore* core = static_cast<GLCore*>(glfwGetWindowUserPointer(window));
        core -> mouseMoved(x,y);
        glfwPollEvents();
    }

};

#endif
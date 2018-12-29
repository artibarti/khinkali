
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
#include "glinputhandler.hpp"

namespace khinkali
{
    class GLCore
    {
        public:
            GLCore(int win_width, int win_height, const char* win_name);
            
            void start();
            void attachScene(GLScene* scene);
            void detachScene();
            void showInfo();
        
        private:
            GLWindow window;
            GLInputHandler inputHandler;
            GLScene* scene;
            std::string window_name = "Unnamed window";
            int window_width = 0;
            int window_height = 0;

            void terminate();
    };

    GLCore::GLCore(int win_width, int win_height, const char* win_name)
    {
        if (!glfwInit())
            return;

        window = GLWindow(win_width, win_height, win_name);
        inputHandler.setWindow(&window);

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

            if (inputHandler.isThereAnyKeyboardInputToHandle())
            {

            }
            if (inputHandler.isThereAnyMouseInputToHandle())
            {

            }

            scene -> draw();

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
        glfwSetWindowShouldClose(window.getWindow(), true);        
        window.destroy();
        glfwTerminate();         
    }

    void GLCore::attachScene(GLScene* scene)
    {
        this -> scene = scene;
    }

    void GLCore::detachScene()
    {
        this -> scene = nullptr;
    }
  
    void GLCore::showInfo()
    {
        std::cout << "GLCore object" << std::endl;
        std::cout << std::endl;
    }
};

#endif
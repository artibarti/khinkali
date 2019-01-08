#ifndef GL_SCENE_H
#define GL_SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>

#include "utils/gltypes.hpp"
#include "utils/gllog.hpp"
#include "utils/glexcepion.hpp"
#include "drawables/gldrawable.hpp"
#include "glcamera.hpp"
#include "glshaderprogram.hpp"
#include "glinputhandler.hpp"
#include "gleventhandler.hpp"

namespace khinkali
{
    class GLScene
    {
        public:
            
            GLScene(int width, int height);

            void setBackground(glm::vec3 color);
            void setBackground(double r, double g, double b);
            void attachDrawable(GLDrawable* drawable);
            void attachProgram(GLShaderProgram *program);            
            
            void setKeyCallback(void(*callback)(KeyEvent*, GLScene*));
            void setMouseCallback(void(*callback)(MouseEvent*, GLScene*));    
            void handleInputAndDraw(KeyEvent* keyEvent, MouseEvent* mouseEvent);
            GLCamera* getCamera();

        private:

            std::vector<GLDrawable*> drawables;
            GLEventHandler<GLScene> eventHandler;
            GLCamera camera;
            GLWindow* window;

            void (*keyCallback)(KeyEvent*, GLScene*) = nullptr;
            void (*mouseCallback)(MouseEvent*, GLScene*) = nullptr;

            int scene_width = 0;
            int scene_height = 0;
            glm::vec3 backgroundColor;       

    };

    GLScene::GLScene(int width, int height)
    {
        scene_width = width;
        scene_height = height;
        camera = GLCamera(scene_width, scene_height);
    }

    void GLScene::setBackground(glm::vec3 color)
    {
        backgroundColor = color;
    }

    void GLScene::setBackground(double r, double g, double b)
    {
        backgroundColor[0] = r;
        backgroundColor[1] = g;
        backgroundColor[2] = b;
    }

    void GLScene::attachDrawable(GLDrawable* drawable)
    {
        drawables.push_back(drawable);
    }

    void GLScene::handleInputAndDraw(KeyEvent* keyEvent, MouseEvent* mouseEvent)
    {
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);
        glClearDepth(1.0);        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (keyEvent != nullptr && keyCallback != nullptr)
        {
            this -> keyCallback(keyEvent, this);
        }

        if (mouseEvent != nullptr && mouseCallback != nullptr)
        {
            this -> mouseCallback(mouseEvent, this);
        }

        for (auto drawable : drawables)
        {
        	glUniformMatrix4fv(UNIFORM_MODELVIEWPROJECTION, 1, GL_FALSE, glm::value_ptr(camera.getModelViewProjectionMatrix()));
        	glUniformMatrix4fv(UNIFORM_NORMAL, 1, GL_FALSE, glm::value_ptr(camera.getNormalMatrix()));
            drawable -> draw();
        }
    }

    void GLScene::attachProgram(GLShaderProgram *program)
    {
        for (auto drawable : drawables)
            drawable -> attachProgram(program);
    }

    void GLScene::setKeyCallback(void(*callback)(KeyEvent*, GLScene*))
    {
        this -> keyCallback = callback;
    }

    void GLScene::setMouseCallback(void(*callback)(MouseEvent*, GLScene*))
    {
        this -> mouseCallback = callback;
    }

    GLCamera* GLScene::getCamera()
    {
        return &camera;
    }
}

#endif
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

namespace khinkali
{
    class GLScene
    {
        public:
            
            GLScene(int width, int height);
            
            void setBackground(glm::vec3 color);
            void setBackground(double r, double g, double b);
            void setSize(int width, int height);
            void addDrawable(std::string tag, GLDrawable* drawable);
            void attachProgram(GLShaderProgram *program);
            void keyPressed(GLint key, GLint scanCode, GLint action, GLint mods);
            void mouseMoved(GLdouble x, GLdouble y);
            void draw();

            void showInfo() const;

        private:

            std::map<std::string, GLShader*> shaders;
            std::map<std::string, GLDrawable*> drawables;

            int scene_width = 0;
            int scene_height = 0;
            glm::vec3 backgroundColor;   
            GLdouble mouseX = -1.0, mouseY = -1.0;

            GLCamera camera;
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

    void GLScene::setSize(int width, int height)
    {
        scene_width = width;
        scene_height = height;
    }

    void GLScene::addDrawable(std::string tag, GLDrawable* drawable)
    {
        auto search = drawables.find(tag);
        if (search != drawables.end())
            throw glDuplicatedObjectNameException();
        else
            drawables[tag] = drawable;
    }

    void GLScene::draw()
    {
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);
        glClearDepth(1.0);        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto drawable : drawables)
        {
        	glUniformMatrix4fv(UNIFORM_MODELVIEWPROJECTION, 1, GL_FALSE, glm::value_ptr(camera.getModelViewProjectionMatrix()));
            drawable.second -> draw();
        }
    }

    void GLScene::attachProgram(GLShaderProgram *program)
    {
        for (auto drawable : drawables)
            drawable.second -> attachProgram(program);
    }

    void GLScene::keyPressed(GLint key, GLint scanCode, GLint action, GLint mods)
    {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            switch(key) 
            {

                case GLFW_KEY_W:
                    camera.moveForward();
                    break;
            
                case GLFW_KEY_S: 
                    camera.moveBack();
                    break;
            
                case GLFW_KEY_A: 
                    camera.moveLeft();
                    break;
            
                case GLFW_KEY_D: 
                    camera.moveRight();
                    break;            
            }
        }        
    }

    void GLScene::mouseMoved(GLdouble x, GLdouble y)
    {        
        if (mouseX == -1.0)
        {
            mouseX = x;
            mouseY = y;
            return;
        }
        
        GLdouble deltaX = x - mouseX;
        GLdouble deltaY = y - mouseY;
        mouseX = x;
        mouseY = y;                

        camera.turn(deltaX, deltaY);
    }

    void GLScene::showInfo() const
    {
        std::cout << "GLScene object" << std::endl;
        std::cout << "Contains " << drawables.size() << " drawables" << std::endl;
    }

}

#endif
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
#include "glshader.hpp"
#include "utils/glexcepion.hpp"
#include "drawables/gldrawable.hpp"
#include "glcamera.hpp"

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
            void addShader(std::string tag, std::string filename, int type);
            void attachShaderToDrawable(std::string shape, std::string shader);
            void attachShadersToDrawable(std::string shape, std::initializer_list<std::string>);
            void showInfo() const;
            void draw();

            void keyPressed(GLint key, GLint scanCode, GLint action, GLint mods);
            void mouseMoved(GLdouble x, GLdouble y);

        private:

            std::map<std::string, GLShader*> shaders;
            std::map<std::string, GLDrawable*> drawables;
            glm::vec3 backgroundColor;   

            int scene_width = 0;
            int scene_height = 0;

            glm::mat4 modelMatrix;
            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;
            glm::mat4 viewProjectionMatrix;

            GLCamera camera;
            GLFWwindow* window;
    };

    GLScene::GLScene(int width, int height)
    {
        scene_width = width;
        scene_height = height;

        addShader("vs", "shaders/default_vertex_shader.vs", GL_VERTEX_SHADER);
        addShader("fs", "shaders/default_fragment_shader.fs", GL_FRAGMENT_SHADER);    

        camera = GLCamera(scene_width, scene_height);
    }

    void GLScene::draw()
    {
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);
        glClearDepth(1.0);        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    glUniformMatrix4fv(UNIFORM_MODEL, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    	glUniformMatrix4fv(UNIFORM_VIEWPROJECTION, 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));

        for (auto drawable : drawables)
            drawable.second -> draw();
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

    void GLScene::addShader(std::string tag, std::string filename, int type)
    {
        GLShader *shader = new GLShader(filename, type);
        shaders[tag] = shader;
    }

    void GLScene::addDrawable(std::string tag, GLDrawable* drawable)
    {
        auto search = drawables.find(tag);
        if (search != drawables.end())
            throw glDuplicatedObjectNameException();
        else
            drawables[tag] = drawable;
    }

    void GLScene::showInfo() const
    {
        std::cout << "GLScene object" << std::endl;
        std::cout << "Contains " << drawables.size() << " drawables" << std::endl;
        std::cout << shaders.size() << " shaders loaded for this scene" << std::endl;
        std::cout << std::endl;
    }

    void GLScene::attachShaderToDrawable(std::string drawable, std::string shader)
    {
        auto search = shaders.find(shader);
        if (search != shaders.end())
            drawables[drawable] -> attachShader(shaders[shader] -> getShader());
        else
            throw glShaderNotLoadedForSceneException();
    }
    
    void GLScene::attachShadersToDrawable(std::string shape, std::initializer_list<std::string> il)
    {
        for (auto shader_name : il)
        {
            attachShaderToDrawable(shape, shader_name);
        }
    }

    void GLScene::setSize(int width, int height)
    {
        scene_width = width;
        scene_height = height;
    }

    void GLScene::keyPressed(GLint key, GLint scanCode, GLint action, GLint mods)
    {

        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            switch(key) 
            {

                case GLFW_KEY_W:
                    camera.setCamPosition ( camera.getCamPosition() + camera.getForward() * camera.getCamSpeed() );
                    break;
            
                case GLFW_KEY_S: 
                    camera.setCamPosition ( camera.getCamPosition() - camera.getForward() * camera.getCamSpeed() ); 
                    break;
            
                case GLFW_KEY_A: 
                    camera.setCamPosition ( camera.getCamPosition() - camera.getRight() * camera.getCamSpeed() ); 
                    break;
            
                case GLFW_KEY_D: 
                    camera.setCamPosition ( camera.getCamPosition() + camera.getRight() * camera.getCamSpeed() ); 
                    break;
            
                case GLFW_KEY_ESCAPE:
                    // exit
                    break;
            }
        }
        
        camera.initMatrices();        
        glfwPollEvents();
    }

    void GLScene::mouseMoved(GLdouble x, GLdouble y)
    {

        if (camera.getMouseX() == -1.0)
        {
            camera.setMouseX(x);
            camera.setMouseY(y);
            return;
        }
        
        GLdouble deltaX = x - camera.getMouseX();
        GLdouble deltaY = y - camera.getMouseY();
        
        camera.setMouseX(x);
        camera.setMouseY(y);
        
        camera.setPitch( glm::clamp<GLfloat>(camera.getPitch() - deltaY * camera.getCamSpeed(), glm::radians(-89.0f), glm::radians(179.0f)) );
        camera.setYaw( camera.getYaw() - deltaX * camera.getCamSpeed() );
        
        camera.initMatrices();        
        glfwPollEvents();
    }


}

#endif
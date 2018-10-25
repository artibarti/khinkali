#ifndef GL_SCENE2D_H
#define GL_SCENE2D_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gltypes.hpp"
#include <string>
#include <vector>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <sstream>
#include <fstream>
#include "gllog.hpp"
#include "glshape.hpp"
#include "glshader.hpp"
#include "glexcepion.hpp"

namespace Lanuka
{

    class GLScene2D
    {
        public:
            GLScene2D();
            GLScene2D(std::string _scene_name, GLFWwindow* window);

            std::string getName() const;
            bool isItYourName(std::string name) const;

            void draw();
            void showInfo() const;
            void setBackground(glm::vec3 color);
            void setBackground(double r, double g, double b);
            void addShape(std::string tag, GLShape* shape);
            void addShader(std::string tag, std::string filename, int type);
            void attachShaderToShape(std::string shader, std::string shape);

        private:
            std::string loadShaderFromFile(const std::string& filename);
            std::string scene_name;
            glm::vec3 backgroundColor;
            
            std::map<std::string, GLShader*> shaders;
            std::map<std::string, GLShape*> shapes;

    };

    GLScene2D::GLScene2D()
    {

    }

    GLScene2D::GLScene2D(std::string _scene_name, GLFWwindow* window)
    {
        scene_name = _scene_name;        
    }

    bool GLScene2D::isItYourName(std::string name) const
    {
        return name == scene_name;
    }

    void GLScene2D::draw()
    {
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0);
        glClearDepth(1.0);        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto shape : shapes)
            shape.second -> draw();
    }

    void GLScene2D::setBackground(glm::vec3 color)
    {
        backgroundColor = color;
    }

    void GLScene2D::setBackground(double r, double g, double b)
    {
        backgroundColor[0] = r;
        backgroundColor[1] = g;
        backgroundColor[2] = b;
    }

    std::string GLScene2D::getName() const
    {
        return scene_name;
    }

    void GLScene2D::showInfo() const
    {
        std::cout << "GLScene object named: " << scene_name << std::endl;
        std::cout << std::endl;
    }

    void GLScene2D::addShape(std::string tag, GLShape* shape)
    {
        auto search = shaders.find(tag);
        if (search != shaders.end())
            throw glDplicatedShapeNameException();
        else
            shapes[tag] = shape;
    }

    void GLScene2D::addShader(std::string tag, std::string filename, int type)
    {
        GLShader *shader = new GLShader(filename, type);
        shaders[tag] = shader;
    }

    void GLScene2D::attachShaderToShape(std::string shader, std::string shape)
    {
        auto search = shaders.find(shader);
        if (search != shaders.end())
            shapes[shape] -> attachShader(shaders[shader] -> getShader());
        else
            throw glShaderNotLoadedForSceneException();
    }

}

#endif
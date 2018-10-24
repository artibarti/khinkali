#ifndef GL_SCENE2D_H
#define GL_SCENE2D_H

#include "gltypes.hpp"
#include <string>
#include <vector>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <sstream>
#include <fstream>
#include "gllog.hpp"
#include "glshape.hpp"

namespace Lanuka
{

    class GLScene2D
    {
        public:
            GLScene2D();
            GLScene2D(std::string _scene_name);

            void draw();
            bool isItYourName(std::string name) const;
            void setBackground(glm::vec3 color);
            void setBackground(double r, double g, double b);
            std::string getName() const;
            void addShape(GLShape* shape);
            void showInfo() const;

        private:
            std::string loadShaderFromFile(const std::string& filename);
            std::vector<GLShape*> shapes;
            std::string scene_name;
            glm::vec3 backgroundColor;
    };

    GLScene2D::GLScene2D()
    {

    }

    GLScene2D::GLScene2D(std::string _scene_name)
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

        for (auto *shape : shapes)
            shape -> draw();
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

    void GLScene2D::addShape(GLShape* shape)
    {
        shapes.push_back(shape);
    }

}

#endif
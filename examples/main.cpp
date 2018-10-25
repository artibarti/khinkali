#include <iostream>
#include "../include/lanuka/lanuka.hpp"

using namespace Lanuka;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test v1.0");
    GLTriangle* triangle = new GLTriangle();
    GLTriangle* triangle2 = new GLTriangle();

    triangle -> setVertices( 
        {
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3( 0.5f, -0.5f, 0.0f),
            glm::vec3( 0.0f,  0.5f, 0.0f)
        });

    triangle -> setColors(
        {
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.7f, 0.7f, 0.7f),
            glm::vec3(0.9f, 0.9f, 1.0f)
        });

    triangle2 -> setVertices( 
        {
            glm::vec3(-0.6f, -0.3f, 0.0f),
            glm::vec3( 0.3f, -0.2f, 0.0f),
            glm::vec3( 0.0f,  0.3f, 0.0f)
        });

    triangle2 -> setColors(
        {
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.7f, 0.7f, 0.7f),
            glm::vec3(0.9f, 0.9f, 1.0f)
        });

    core.addScene("Test scene");

    core.lookupScene("Test scene").setBackground(0.9,0.5,0.0);
    core.lookupScene("Test scene").addShape("my triangle", triangle);
    core.lookupScene("Test scene").addShape("my triangle2", triangle2);
    core.lookupScene("Test scene").addShader("vs", "shaders/first.vs", GL_VERTEX_SHADER);
    core.lookupScene("Test scene").addShader("fs", "shaders/first.fs", GL_FRAGMENT_SHADER);
    core.lookupScene("Test scene").attachShaderToShape("vs", "my triangle");
    core.lookupScene("Test scene").attachShaderToShape("fs", "my triangle");
    core.lookupScene("Test scene").attachShaderToShape("vs", "my triangle2");
    core.lookupScene("Test scene").attachShaderToShape("fs", "my triangle2");
    core.start();
    
}

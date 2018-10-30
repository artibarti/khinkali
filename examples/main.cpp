#include <iostream>
#include "../include/lanuka/lanuka.hpp"

using namespace Lanuka;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test window");
    
    GLTriangle triangle
    (
        glm::vec2(-0.5, -0.5), 
        glm::vec2( 0.5, -0.5), 
        glm::vec2( 0.0, 0.5)
    );
    triangle.setColor(GL_COLOR_BLUE);

    GLTriangle triangle2
    (
        glm::vec2(-0.3, -0.7), 
        glm::vec2( 0.2, -0.5), 
        glm::vec2( 0.2, 0.4)
    );
    triangle2.setColor(GL_COLOR_GREEN);

    GLRectangle rect
    (
        glm::vec2(0.7, 0.7),
        glm::vec2(0.7, -0.7),
        glm::vec2(-0.7, 0.7),
        glm::vec2(-0.7, -0.7)
    );
    rect.setColor(GL_COLOR_WHITE);
        
    GLScene2D scene("Test scene");
    core.attachScene(&scene);
    scene.setBackground(GL_COLOR_RED);
    scene.addShape("my rect", &rect);
    scene.addShape("my triangle", &triangle);
    scene.addShape("my triangle2", &triangle2);
    scene.addShader("vs", "shaders/vertex_shader.vs", GL_VERTEX_SHADER);
    scene.addShader("fs", "shaders/fragment_shader.fs", GL_FRAGMENT_SHADER);
    scene.attachShadersToShape("my triangle", {"vs", "fs"});
    scene.attachShadersToShape("my triangle2", {"vs", "fs"});
    scene.attachShadersToShape("my rect", {"vs", "fs"});
    core.start();

}

#include <iostream>
#include "../include/khinkali/khinkali.hpp"

using namespace khinkali;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test window");

    /*

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
        glm::vec2(-0.7, 0.9),
        glm::vec2(-0.7, -0.9)
    );
    rect.setColor(GL_COLOR_WHITE);

    GLScene scene = GLScene(640,480);
    core.attachScene(0, &scene);
    scene.setBackground(GL_COLOR_RED);

    scene.addDrawable("my rect", &rect);
    scene.addDrawable("my triangle", &triangle);
    scene.addDrawable("my triangle2", &triangle2);

    scene.addShader("vs", "shaders/static_view_vertex_shader.vs", GL_VERTEX_SHADER);
    scene.addShader("fs", "shaders/static_view_fragment_shader.fs", GL_FRAGMENT_SHADER);
    //scene.addShader("vs", "shaders/default_vertex_shader.vs", GL_VERTEX_SHADER);
    //scene.addShader("fs", "shaders/default_fragment_shader.fs", GL_FRAGMENT_SHADER);

    scene.attachShadersToDrawable("my triangle", {"vs", "fs"});
    scene.attachShadersToDrawable("my triangle2", {"vs", "fs"});
    scene.attachShadersToDrawable("my rect", {"vs", "fs"});

    */

    GLCube cube = GLCube(glm::vec3(0,0,0), 1.0);
    cube.setColor(GL_COLOR_BLUE);

    GLScene scene = GLScene(640,480);
    core.attachScene(0, &scene);
    scene.setBackground(GL_COLOR_RED);
    scene.addDrawable("my cube", &cube);

    scene.addShader("vs", "shaders/static_view_vertex_shader.vs", GL_VERTEX_SHADER);
    scene.addShader("fs", "shaders/static_view_fragment_shader.fs", GL_FRAGMENT_SHADER);
    scene.attachShadersToDrawable("my cube", {"vs", "fs"});

    core.start();

}

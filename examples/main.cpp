#include <iostream>
#include "../include/khinkali/khinkali.hpp"

using namespace khinkali;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test window");

    GLCube cube1 = GLCube(glm::vec3(0,0,0), 1.0);
    cube1.setColor(GL_COLOR_BLUE);
    GLCube cube2 = GLCube(glm::vec3(0,1,0), 1.0);
    cube2.setColor(GL_COLOR_GREEN);
    GLCube cube3 = GLCube(glm::vec3(1,0,0), 1.0);
    cube3.setColor(GL_COLOR_BLUE);

    GLScene scene = GLScene(640,480);
    core.attachScene(0, &scene);
    scene.setBackground(GL_COLOR_ORANGE);
    scene.addDrawable("my cube1", &cube1);
    scene.addDrawable("my cube2", &cube2);
    scene.addDrawable("my cube3", &cube3);

    GLShaderProgram program;
    program.attachShader(0, "shaders/static_view_vertex_shader.vs", GL_VERTEX_SHADER);
    program.attachShader(0, "shaders/static_view_fragment_shader.fs", GL_FRAGMENT_SHADER);
    scene.attachProgram(&program);

    core.start();
}

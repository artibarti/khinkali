#include <iostream>
#include "../include/khinkali/khinkali.hpp"

using namespace khinkali;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test window");

    GLCube cube1 = GLCube(glm::vec3(0,0,0), 1.0);
    GLCube cube2 = GLCube(glm::vec3(0,1,0), 1.0);
    GLCube cube3 = GLCube(glm::vec3(1,0,0), 1.0);

    GLCube cube4 = GLCube(glm::vec3(-2,0,0), 1.0);
    GLCube cube5 = GLCube(glm::vec3(-2,1,0), 1.0);
    GLCube cube6 = GLCube(glm::vec3(-3,0,0), 1.0);

    GLCube cube7 = GLCube(glm::vec3(2,0,-2), 1.0);
    GLCube cube8 = GLCube(glm::vec3(3,0,-2), 1.0);

    GLCube floor = GLCube(glm::vec3(0,-15,0), 30.0);

    GLScene scene = GLScene(640,480);
    core.attachScene(0, &scene);
    scene.setBackground(GL_COLOR_ORANGE);

    scene.addDrawable("my cube1", &cube1);
    scene.addDrawable("my cube2", &cube2);
    scene.addDrawable("my cube3", &cube3);
    scene.addDrawable("my cube4", &cube4);
    scene.addDrawable("my cube5", &cube5);
    scene.addDrawable("my cube6", &cube6);
    scene.addDrawable("my cube7", &cube7);
    scene.addDrawable("my cube8", &cube8);
    scene.addDrawable("my floor", &floor);

    GLShaderProgram program;
    program.attachShader(0, "shaders/texture.vs", GL_VERTEX_SHADER);
    program.attachShader(0, "shaders/texture.fs", GL_FRAGMENT_SHADER);
    scene.attachProgram(&program);

    core.start();
}

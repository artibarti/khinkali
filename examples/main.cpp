#include <iostream>
#include "../include/khinkali/khinkali.hpp"

using namespace khinkali;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test window");

    std::vector<GLCube*> cubes;    

    GLCube cube1 = GLCube(glm::vec3(0,0,0), 1.0);
    GLCube cube2 = GLCube(glm::vec3(0,1,0), 1.0);
    GLCube cube3 = GLCube(glm::vec3(1,0,0), 1.0);
    GLCube cube4 = GLCube(glm::vec3(-2,0,0), 1.0);
    GLCube cube5 = GLCube(glm::vec3(-2,1,0), 1.0);
    GLCube cube6 = GLCube(glm::vec3(-3,0,0), 1.0);
    GLCube cube7 = GLCube(glm::vec3(2,0,-2), 1.0);
    GLCube cube8 = GLCube(glm::vec3(3,0,-2), 1.0);
    
    GLCube cube9 = GLCube(glm::vec3(-7,0,-2), 1.0);
    GLCube cube10 = GLCube(glm::vec3(-7,1,-2), 1.0);
    GLCube cube11 = GLCube(glm::vec3(-9,0,-2), 1.0);
    GLCube cube12 = GLCube(glm::vec3(-7,2,-2), 1.0);
    GLCube cube13 = GLCube(glm::vec3(-7,3,-2), 1.0);
    GLCube cube14 = GLCube(glm::vec3(-9,1,-2), 1.0);
    GLCube cube15 = GLCube(glm::vec3(-9,2,-2), 1.0);
    GLCube cube16 = GLCube(glm::vec3(-9,3,-2), 1.0);
    GLCube cube17 = GLCube(glm::vec3(-8,3,-2), 1.0);

    GLCube floor = GLCube(glm::vec3(0,-15,0), 30.0);


    cubes = 
    {
        &cube1, &cube2, &cube3, &cube4, &cube5, &cube6, &cube7, &cube8,
        &cube9, &cube10, &cube11, &cube12, &cube13, &cube14, &cube15, &cube16, &cube17
    };

    GLScene scene = GLScene(640,480);
    core.attachScene(0, &scene);
    scene.setBackground(GL_COLOR_ORANGE);

    GLTexture brick_texture("textures/bricks.jpg");
    for (auto cube : cubes)
    {
        scene.attachDrawable(cube);
        cube -> attachTexture(&brick_texture);
    }

    GLTexture chess_texture("textures/grass2.jpg");    
    floor.attachTexture(&chess_texture);
    scene.attachDrawable(&floor);

    GLShaderProgram program;
    program.attachShader(0, "shaders/texture.vs", GL_VERTEX_SHADER);
    program.attachShader(0, "shaders/texture.fs", GL_FRAGMENT_SHADER);
    scene.attachProgram(&program);

    core.start();

}

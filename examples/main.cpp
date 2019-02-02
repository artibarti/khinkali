#include <iostream>
#include "../include/khinkali/khinkali.hpp"

using namespace khinkali;

void keyCallback(KeyEvent* keyEvent, GLScene* scene)
{
    if (keyEvent -> actions == GLFW_PRESS || keyEvent -> actions == GLFW_REPEAT)
    {
        switch(keyEvent -> key) 
        {
            case GLFW_KEY_W:
                scene -> getCamera() -> moveForward();
                break;
            case GLFW_KEY_S: 
                scene -> getCamera() -> moveBack();
                break;            
            case GLFW_KEY_A: 
                scene -> getCamera() -> moveLeft();
                break;            
            case GLFW_KEY_D: 
                scene -> getCamera() -> moveRight();
                break;            
            case GLFW_KEY_ESCAPE:
                scene -> detach();
                break;            
        }
    }                
}

GLdouble mouseX = -1.0, mouseY = -1.0;

void mouseCallback(MouseEvent* mouseEvent, GLScene* scene)
{   
    if (mouseX == -1.0)
    {
        mouseX = mouseEvent -> x;
        mouseY = mouseEvent -> y;
        return;
    }
    
    GLdouble deltaX = mouseEvent -> x - mouseX;
    GLdouble deltaY = mouseEvent -> y - mouseY;
    mouseX = mouseEvent -> x;
    mouseY = mouseEvent -> y;                
    scene -> getCamera() -> turn(deltaX, deltaY);
}

bool trigger(GLScene* scene, GLDrawable* drawable)
{
    return true;
}

void callback(GLDrawable* drawable) 
{

}

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test window");

    GLScene scene = GLScene(640,480);
    scene.setBackground(GL_COLOR_ORANGE);
    
    scene.setKeyCallback(keyCallback);
    scene.setMouseCallback(mouseCallback);
    
    core.attachScene(&scene);

    GLCube cube = GLCube(glm::vec3(0,0,0), 1.0);
    GLCube floor = GLCube(glm::vec3(0,-15,0), 30.0);

    GLTexture brick_texture("textures/bricks.jpg");
    GLTexture chess_texture("textures/grass2.jpg");    

    floor.attachTexture(&chess_texture);
    cube.attachTexture(&brick_texture);

    scene.attachDrawable(&cube);
    scene.attachDrawable(&floor);

    GLEvent myEvent(trigger, callback);

    scene.attachEventSubsribtion(&myEvent, &cube);

    /*GLShaderProgram program;
    program.attachShader(0, "shaders/texture.vs", GL_VERTEX_SHADER);
    program.attachShader(0, "shaders/texture.fs", GL_FRAGMENT_SHADER);
    scene.attachProgram(&program);*/

    core.start();

}

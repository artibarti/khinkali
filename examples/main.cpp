#include <iostream>
#include "../include/lanuka/lanuka.hpp"

using namespace Lanuka;

int main(int argc, char** argv)
{

    GLCore core(640, 480, "Test v1.0");
    GLTriangle* triangle = new GLTriangle();
    core.addScene("Test scene");
    core.lookupScene("Test scene").setBackground(0.0, 0.7, 0.3);
    core.lookupScene("Test scene").addShape("my triangle", triangle);
    core.start();
    
}

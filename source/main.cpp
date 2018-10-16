#include "lika/lvector.hpp"
#include "lika/lmatrix.hpp"
#include <iostream>

using namespace Lika;

int main(int argc, char** argv)
{
	std::cout << "Khinkali graphics library test version..." << std::endl;

    vec3i v1;
    vec3d v2 {1,2,3};
    vec3d v3 {1,2,5};

    v3 = v2;
    v3.showInfo();
    v3.reverse().showInfo();
    
    vec4d v4 {2, -2, 3 ,-4};

    vec3i v5 {4,0,0};
    vec3i v6 {0,-3,0};

    std::cout << v5.getNorm() << std::endl;
    std::cout << v5.getDistanceFrom(v6) << std::endl;

    mat2x2d m1 
    {
        {2,5},
        {5,6}
    };

    mat2x2d m2 
    {
        {1,5},
        {5,1}
    };

    (m1+m2).showInfo();

    mat4x4i m3
    {
        {1,2,3,4},
        {1,2,3,5},
        {1,2,3,6},
        {1,2,3,7},
    };

    Lika::Matrix<int,1,4> m4 
    {
        {1,2,3,4}
    };

}

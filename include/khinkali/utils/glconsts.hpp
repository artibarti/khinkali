#ifndef GL_CONSTS_H
#define GL_CONSTS_H

#include <glm/vec3.hpp>
#include <map>
#include <string>
#include "gltypes.hpp"

namespace khinkali
{
    const glm::vec3 GL_COLOR_RED = {1.0, 0.0, 0.0};
    const glm::vec3 GL_COLOR_BLUE = {0.0, 0.0, 1.0};
    const glm::vec3 GL_COLOR_GREEN = {0.0, 1.0, 0.0};
    const glm::vec3 GL_COLOR_BLACK = {0.0, 0.0, 0.0};
    const glm::vec3 GL_COLOR_WHITE = {1.0, 1.0, 1.0};
    const glm::vec3 GL_COLOR_ORANGE = {0.9, 0.5, 0.0};
    const glm::vec3 GL_COLOR_GREY = {0.5, 0.5, 0.5};
    const glm::vec3 GL_COLOR_LIGHTBLUE = {0.2, 0.3, 1.0};

    const int UNIFORM_MODELVIEWPROJECTION = 0;
    const int UNIFORM_NORMAL = 1;
    const int VERTEX_ATTRIB_POS = 0;
    const int VERTEX_ATTRIB_UV = 1;
    const int VERTEX_ATTRIB_NORMAL = 2;
    const int VERTEX_ATTRIB_COLOR = 3;

    std::map<GLDrawableType, int> vertexNumberConstraintForDrawables =
    {
        {GL_DRAWABLE_TYPE_TRIANGLE, 3},
        {GL_DRAWABLE_TYPE_RECTANGLE, 4},
        {GL_DRAWABLE_TYPE_CUBE, 24}
    };

    std::string defaultVertexShader = 
    
        "#version 430"

        "#define UNIFORM_MVP          0"
        "#define UNIFORM_NORMAL       1"
        "#define VERTEX_ATTRIB_POS    0"
        "#define VERTEX_ATTRIB_UV     1"
        "#define VERTEX_ATTRIB_NORMAL 2"

        "layout (location = UNIFORM_MVP) uniform mat4 mMVP;"
        "layout (location = UNIFORM_NORMAL) uniform mat4 mNormal;"
        "layout (location = VERTEX_ATTRIB_POS) in vec3 vPos;"
        "layout (location = VERTEX_ATTRIB_UV) in vec2 vUV;"
        "layout (location = VERTEX_ATTRIB_NORMAL) in vec3 vNormal;"

        "out vec2 vUVVS;"
        "out vec3 vNormalVS;"

        "void main()"
        "{"
        "vUVVS = vUV;"
        "vNormalVS = normalize(vec3(mNormal * vec4(vNormal, 0)));    "
        "gl_Position = mMVP * vec4(vPos, 1);"
        "}";

    std::string defaultFragmentShader = 
    
        "#version 430"

        "in vec2 vUVVS;"
        "in vec3 vNormalVS;"

        "out vec4 outColor;"

        "const vec3 vLightDirWS = vec3(0.0, 1.0, 0.0);"

        "layout (binding = 0) uniform sampler2D sTexture;"

        "void main()"
        "{"
            "vec3 vNormalWS = normalize(vNormalVS);"
            "// float fLightIntensity = max(dot(vNormalWS, vLightDirWS), 0.0);"
            "vec3 textureColor = texture2D(sTexture, vUVVS).rgb;"
            "// outColor = vec4(fLightIntensity * textureColor, 1);"
            "outColor = vec4(textureColor, 1);"
        "}";

};



#endif
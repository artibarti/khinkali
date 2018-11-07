#version 430

#define UNIFORM_MVP          0
#define UNIFORM_NORMAL       1

#define VERTEX_ATTRIB_POS    0
#define VERTEX_ATTRIB_UV     1
#define VERTEX_ATTRIB_NORMAL 2

layout (location = UNIFORM_MVP) uniform mat4 mMVP;
layout (location = UNIFORM_NORMAL) uniform mat4 mNormal;

layout (location = VERTEX_ATTRIB_POS) in vec3 vPos;
layout (location = VERTEX_ATTRIB_UV) in vec2 vUV;
layout (location = VERTEX_ATTRIB_NORMAL) in vec3 vNormal;

out vec2 vUVVS;
out vec3 vNormalVS;

void main()
{
    vUVVS = vUV;
    vNormalVS = normalize(vec3(mNormal * vec4(vNormal, 0)));    
    gl_Position = mMVP * vec4(vPos, 1);
}
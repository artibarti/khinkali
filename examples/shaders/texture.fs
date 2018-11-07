#version 430

in vec2 vUVVS;
in vec3 vNormalVS;

out vec4 outColor;

const vec3 vLightDirWS = vec3(0.0, 1.0, 0.0);

layout (binding = 0) uniform sampler2D sTexture;

void main()
{
    vec3 vNormalWS = normalize(vNormalVS);
    // float fLightIntensity = max(dot(vNormalWS, vLightDirWS), 0.0);
    vec3 textureColor = texture2D(sTexture, vUVVS).rgb;   
    // outColor = vec4(fLightIntensity * textureColor, 1);
    outColor = vec4(textureColor, 1);
}
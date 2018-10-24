#version 430

/** Egyetlen bemeneti attribútumunk, a szín. Nagyon lényeges,
    hogy a nevének egyeznie kell az előző shaderben megadottal. */
in vec3 vColorVS;

/** Egyetlen pufferbe írunk csak, amely az ablakunkban jelenik
    meg, így egyetlen kimeneti attribútumunk van. */
out vec4 outColor;

void main()
{
    /** Írjuk ki az adott fragment (pixel) színét. */
    outColor = vec4(vColorVS, 1);
}
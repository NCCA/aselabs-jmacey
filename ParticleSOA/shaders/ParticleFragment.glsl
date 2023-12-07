#version 410 core

layout (location =0) out vec4 fragColour;
in vec3 particleColour;
void main()
{

    vec2 circCord = 2.0 * gl_PointCoord - 1.0;
    if(dot(circCord,circCord) > 1.0)
    {
        discard;
    }

    fragColour.rgb=particleColour;
}
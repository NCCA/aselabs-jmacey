#version 410 core
layout (location = 0) in vec3 inPos;
layout( location =1) in vec3 inColour;
uniform mat4 MVP;
out vec3 particleColour;
void main()
{
    particleColour=inColour;
    gl_Position = MVP * vec4(inPos,1);
}
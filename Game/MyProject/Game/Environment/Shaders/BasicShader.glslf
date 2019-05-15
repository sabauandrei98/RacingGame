#version 150

in vec2 uv;
int vec3 color;

out vec4 fragColor;


void main()
{
    fragColor= vec4(color,1.0);
}





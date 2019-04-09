#version 150

in vec3 color;
out vec4 fragColor;

uniform vec3 unifColor;

void main()
{
    fragColor=vec4(color,1.);
    //fragColor = vec4(unifColor,1.);
}

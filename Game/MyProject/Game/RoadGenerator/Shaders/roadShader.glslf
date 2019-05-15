#version 150

in vec2 uv;
in vec3 color;

uniform sampler2D roadTexture;

out vec4 fragColor;

void main()
{
    fragColor=texture(roadTexture,uv)*vec4(color,1.0);
}

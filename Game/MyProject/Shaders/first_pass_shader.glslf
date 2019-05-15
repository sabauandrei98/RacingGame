#version 330

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec4 color;

in vec3 pos;
in vec3 norm;
in vec2 uv;

uniform sampler2D TEXTURE;

void main() 
{
	position = pos;
	
    normal = texture(TEXTURE, uv).rgb;

    color.rgba = vec4(normalize(norm)* 0.5 + 0.5,1.0);//normalize(pos) * 0.5 + 0.5;
}
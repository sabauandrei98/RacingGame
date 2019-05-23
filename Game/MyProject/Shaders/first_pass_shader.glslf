#version 330

layout(location = 0) out vec4 position;
layout(location = 1) out vec4 normal;
layout(location = 2) out vec4 color;

in vec3 pos;
in vec3 norm;
in vec2 uv;

uniform mat4 IvModelViewProjectionMatrix;
uniform sampler2D TEXTURE;

void main() 
{
	position = vec4(pos, 1.f);
    normal = vec4(normalize(norm), 1.f);
    color = texture(TEXTURE, uv);
}
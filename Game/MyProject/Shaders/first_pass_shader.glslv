uniform mat4 IvModelViewProjectionMatrix;
uniform mat4 IvWorldMatrix;

layout(location = POSITION) in vec3 position;
layout(location = NORMAL) in vec3 normal;
layout(location = TEXCOORD0) in vec2 texcoords;

out vec3 pos;
out vec3 norm;
out vec2 uv;

void main() 
{
    gl_Position = IvModelViewProjectionMatrix * vec4(position, 1.);
    pos = gl_Position.xyz;//(IvWorldMatrix * vec4(position, 1.)).xyz;
    norm = normal;
    uv = texcoords;
}
uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 Position;
layout(location = TEXCOORD0) in vec2 texCoord;
layout(location = COLOR) in vec3 color;

out vec2 uv;
out vec3 normal;
out vec3 m_color;

void main()
{
m_color=color;
gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);

}

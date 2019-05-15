uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 Position;
layout(location = TEXCOORD0) in vec2 texCoord;
layout(location = COLOR) in vec3 Color;

out vec2 uv;
out vec3 normal;
out vec3 color;

void main()
{
color=Color;
gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);
uv=texCoord.xy;
}



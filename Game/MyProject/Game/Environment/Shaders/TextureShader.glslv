uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 Position;
layout(location = TEXCOORD0) in vec2 texCoord;

out vec2 uv;
out vec3 normal;

void main()
{
    gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);
    uv=texCoord.xy;
}


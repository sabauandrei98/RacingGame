uniform mat4 IvModelViewProjectionMatrix;
uniform mat4 IvModelViewMatrix;

layout(location = POSITION) in vec3 Position;

layout(location = TEXCOORD0) in vec2 texCoord;

layout(location = NORMAL) in vec3 aNormal;

out vec2 uv;
out vec4 pos;
out vec3 normal;
out float height;

void main()
{
    gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);
    uv=texCoord.xy;
    pos = IvModelViewMatrix * vec4(Position, 1.0);
	normal = aNormal;
    height = Position.y;
}

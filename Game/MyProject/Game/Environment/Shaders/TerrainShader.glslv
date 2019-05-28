//uniform mat4 IvModelViewProjectionMatrix;
//uniform mat4 IvModelViewMatrix;
//
//layout(location = POSITION) in vec3 Position;
//
//layout(location = TEXCOORD0) in vec2 texCoord;
//
//layout(location = NORMAL) in vec3 aNormal;
//
//out vec2 uv;
//out vec4 pos;
//out vec3 normal;
//out float height;
//
//void main()
//{
//    gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);
//    uv=texCoord.xy;
//    pos = IvModelViewMatrix * vec4(Position, 1.0);
//    normal = aNormal;
//    height = Position.y;
//}

uniform mat4 IvModelViewProjectionMatrix;
uniform mat4 IvModelViewMatrix;
uniform mat4 IvWorldMatrix;

layout(location = POSITION) in vec3 position;
layout(location = NORMAL) in vec3 normal;
layout(location = TEXCOORD0) in vec2 texcoords;

out vec3 pos;
out vec3 norm;
out vec2 uv;

vec3 calculateNormal() {
    mat3 normalMatrix = transpose(inverse(mat3(IvWorldMatrix)));
    return normalMatrix * normal;
}

void main()
{
    gl_Position = IvModelViewProjectionMatrix * vec4(position, 1.);
    pos = (IvModelViewMatrix * vec4(position, 1.)).xyz;
    norm = normal;
    uv = texcoords;
}

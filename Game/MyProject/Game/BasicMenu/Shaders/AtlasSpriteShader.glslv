uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 Position;
layout(location = TEXCOORD0) in vec2 texCoord;

out vec2 uv;

uniform float row;
uniform float column;

const float noRows=10;
const float noColumns=10;

vec2 getSpriteUv(in vec2 v,in float r,in float c)
{
    float y=1.0/noRows;
    float x=1.0/noColumns;

    vec2 scale=vec2(x,y);
    vec2 translate=vec2( x * c , y * r );

    return v * scale + translate;
}

void main()
{
    gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);
    uv=getSpriteUv(texCoord.xy,row,column);
}

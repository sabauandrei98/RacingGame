uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 IvPos;
layout(location = TEXCOORD0) in vec2 IvUv;
layout(location = COLOR) in vec3 IvColor;

out vec2 uv;
out vec3 color;

void main()
{
    color=IvColor;
    gl_Position =  IvModelViewProjectionMatrix * vec4(IvPos,1.0);
    uv=IvUv.xy;
}


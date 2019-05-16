uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 IvPos;
layout(location = COLOR) in vec3 IvColor;

out vec3 color;

void main()
{
    color=IvColor;
    gl_Position =  IvModelViewProjectionMatrix * vec4(IvPos,1.0);
}


uniform mat4 IvModelViewProjectionMatrix;

in vec3 IvPos;
in vec3 IvColor;

out vec3 color;

void main()
{
    color=IvColor;
    gl_Position =  vec4(IvPos,1.0);
}


uniform mat4 IvModelViewProjectionMatrix;

in vec3 IvPos;
in vec3 IvColor;
in vec2 IvCoord;

out vec3 color;
out vec2 uvCoord;

void main()
{
    color=IvColor;
    uvCoord=IvCoord;
    gl_Position =  vec4(IvPos,1.0);
}

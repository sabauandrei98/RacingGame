in vec3 IvPos;
in vec2 IvCoord;

out vec2 uvCoord;

void main()
{
    uvCoord=IvCoord;
    gl_Position = vec4(IvPos,1.0);
}

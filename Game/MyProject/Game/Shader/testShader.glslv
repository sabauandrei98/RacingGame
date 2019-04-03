uniform mat4 IvModelViewProjectionMatrix;

in vec3 IvPos;

//layout(location=COLOR) in vec4 color;
//layout(location = TEXCOORD0) in vec2 texCoord;



void main()
{
   gl_Position =  vec4(IvPos,1.0);
}

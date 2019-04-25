#version 150

in vec2 uv;

uniform sampler2D myTexture;

//uniform vec4 color;

out vec4 fragColor;


void main()
{
	fragColor=texture(myTexture,uv);  //
}


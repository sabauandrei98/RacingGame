#version 150

in vec2 uv;

uniform sampler2D mTexture;

//uniform vec4 color;

out vec4 fragColor;


void main()
{
	fragColor=texture(mTexture,uv);  //
}


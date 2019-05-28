#version 150

in vec2 uv;

uniform sampler2D mTexture;

out vec4 fragColor;


void main()
{
    fragColor=texture(mTexture,uv).aaaa ;
}


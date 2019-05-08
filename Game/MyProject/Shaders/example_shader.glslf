#version 150

in vec4 col;
in vec2 uv;

//uniform float TEXTURE_OR_COLOR;
uniform sampler2D TEXTURE;
uniform vec4 COLOR;

out vec4 fragColor;

void main() {
	
		//float a = TEXTURE_OR_COLOR;
 		fragColor = texture(TEXTURE, uv);
}

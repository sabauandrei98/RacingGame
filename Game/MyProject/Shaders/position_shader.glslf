#version 330

in vec2 uv;

out vec4 fragColor;

uniform sampler2D POS;

void main() {
	fragColor = texture(POS, uv);
}
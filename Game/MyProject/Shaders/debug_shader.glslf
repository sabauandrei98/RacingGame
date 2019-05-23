#version 150

in vec4 col;
in vec2 uv;

out vec4 fragColor;

uniform sampler2D TEXTURE;

void main() {
    fragColor = texture(TEXTURE, uv);
}

#version 150

uniform sampler2D TEXTURE;

in vec2 uv;
in vec4 color;

out vec4 fragColor;

void main() {
    fragColor = texture(TEXTURE, uv);
}

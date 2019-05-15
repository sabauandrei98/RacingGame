#version 150

in vec2 uv;

out vec4 fragColor;

uniform sampler2D TEXTURE;

void main() {
    fragColor = texture(TEXTURE, uv);
    fragColor = vec4(fragColor.rgba);
}

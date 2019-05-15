layout(location = POSITION) in vec4 position;

out vec2 uv;

void main() {
    gl_Position = position;
    uv = vec2((position.x + 1.f) / 2.f, (position.y + 1.f) / 2.f);
}
layout(location = POSITION) in vec4 position;

out vec2 uv;

void main() {
    gl_Position = position;
    uv = vec2((position.x + 1.) / 2., (position.y + 1.) / 2.);
}
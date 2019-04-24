uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec4 position;
layout(location = COLOR) in vec4 color;

out vec4 col;

void main() {
    gl_Position = IvModelViewProjectionMatrix * position;
    col = color;
}

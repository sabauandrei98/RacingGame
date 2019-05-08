uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec4 position;
layout(location = COLOR) in vec4 color;
layout(location = TEXCOORD0) in vec2 texcoords;

out vec4 col;
out vec2 uv;

void main() {
    gl_Position = IvModelViewProjectionMatrix * position;
    col = color;
    uv = texcoords;
}

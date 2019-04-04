uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec4 position;

void main() {
    gl_Position = IvModelViewProjectionMatrix * position;
}

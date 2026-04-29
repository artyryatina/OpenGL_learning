#version 330 core
out vec4 ourColor;

in vec4 aPos;
in vec4 aUV;

void main() {
    gl_Position = aPos;
}
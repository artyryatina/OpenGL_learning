#version 330 core
out vec4 ourColor;

in vec4 aPos;
uniform vec4 uShift;

void main() {
    gl_Position = aPos + uShift;
}
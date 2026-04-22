#version 330 core
out vec4 ourColor;

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;

void main() {
    gl_Position = aPos;
    ourColor = aColor;
}
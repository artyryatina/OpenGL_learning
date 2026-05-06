#version 330 core
out vec4 ourColor;

in vec4 aPos;
in vec2 aUV;

out vec2 vTexCoords;

uniform mat4 uTransformation;

void main() {
    vTexCoords = aUV;
    vTexCoords.y = 1.0 - vTexCoords.y;
    gl_Position = uTransformation * aPos;
}
#version 330 core

in vec2 vTexCoords;

uniform sampler2D uTextureHouse;
uniform sampler2D uTextureGirl;
uniform sampler2D uTextureField;
uniform sampler2D uTextureGhost;

out vec4 FragColor;

void main() {
    vec4 colorHouse = texture(uTextureHouse, vTexCoords);
    vec4 colorGirl = texture(uTextureGirl, vTexCoords);
    vec4 colorField = texture(uTextureField, vTexCoords);
    vec4 colorGhost = texture(uTextureGhost, vTexCoords);
    FragColor = colorGirl; // Колір отриманий із текстури
}
#version 330 core

in vec4 aPos;
in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vNormal;      // нормаль у світовому просторі
out vec3 vWorldPos;     // позиція фрагмента у світовому просторі

void main() {
    vWorldPos = vec3(uModel * aPos);

    vNormal = mat3(transpose(inverse(uModel))) * aNormal;

    mat4 MVP = uProjection * uView * uModel;
    gl_Position = MVP * aPos;
}
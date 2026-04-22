//
// Created by artyr on 22.04.2026.
//

#ifndef OPENGL_LEARNING_SHADER_UTILS_H
#define OPENGL_LEARNING_SHADER_UTILS_H

#include <string>

#include "glad/glad.h"


std::string LoadShaderFromFile(const std::string &filePath);
GLuint  createShader(std::string &filePath, GLuint shaderType);
GLuint createProgram(
    std::string &vertexShaderName,
    std::string &fragmentShaderName);

#endif //OPENGL_LEARNING_SHADER_UTILS_H

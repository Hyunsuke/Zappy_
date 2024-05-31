/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLShader
*/

#include "gui.hpp"

RLShader::RLShader(const std::string& vertexPath, const std::string& fragmentPath) {
    shader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());
}

RLShader::~RLShader() {
    UnloadShader(shader);
}

Shader RLShader::GetShader() const {
    return shader;
}

void RLShader::SetShaderValue(const std::string& uniformName, const void* value, int uniformType) {
    int loc = GetShaderLocation(shader, uniformName.c_str());
    ::SetShaderValue(shader, loc, value, uniformType);
}

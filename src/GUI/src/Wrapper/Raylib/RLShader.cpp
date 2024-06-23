/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLShader
*/

#include "gui.hpp"

Shader RLShader::LoadShader(const std::string& vsFileName, const std::string& fsFileName) {
    return ::LoadShader(vsFileName.c_str(), fsFileName.c_str());
}

void RLShader::UnloadShader(Shader shader) {
    ::UnloadShader(shader);
}

void RLShader::BeginShaderMode(Shader shader) {
    ::BeginShaderMode(shader);
}

void RLShader::SetShaderValue(Shader shader, int uniformLoc, const Vector3& value, int uniformType) {
    ::SetShaderValue(shader, uniformLoc, &value, uniformType);
}

int RLShader::GetShaderLocation(Shader shader, const std::string& uniformName) {
    return ::GetShaderLocation(shader, uniformName.c_str());
}
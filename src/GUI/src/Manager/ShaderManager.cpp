/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ShaderManager
*/

#include "gui.hpp"

ShaderManager::ShaderManager(const std::string& vertexPath, const std::string& fragmentPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath) {
    shader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());
}

ShaderManager::~ShaderManager() {
    if (shader.id != 0) {
        UnloadShader(shader);
    }
}

void ShaderManager::UseShader() {
    BeginShaderMode(shader);
}

void ShaderManager::SetShaderValue(const std::string& uniformName, const void* value, int uniformType) {
    int location = GetUniformLocation(uniformName);
    ::SetShaderValue(shader, location, value, uniformType);
}

Shader ShaderManager::GetShader() const {
    return shader;
}

int ShaderManager::GetUniformLocation(const std::string& uniformName) {
    return GetShaderLocation(shader, uniformName.c_str());
}

/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ShaderManager
*/

#include "gui.hpp"

ShaderManager::ShaderManager(const std::string& vertexPath, const std::string& fragmentPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath) {
    shader = rlShader.LoadShader(vertexPath.c_str(), fragmentPath.c_str());
    if (shader.id == 5) {
        throw GameException("Failed to load shader: " + vertexPath + " " + fragmentPath);
    }
}

ShaderManager::~ShaderManager() {
    if (shader.id != 0) {
        rlShader.UnloadShader(shader);
    }
}

void ShaderManager::UseShader() {
    rlShader.BeginShaderMode(shader);
}

void ShaderManager::SetShaderValue(const std::string& uniformName, const Vector3& value, int uniformType) {
    int location = GetUniformLocation(uniformName);
    rlShader.SetShaderValue(shader, location, value, uniformType);
}

Shader ShaderManager::GetShader() const {
    return shader;
}

int ShaderManager::GetUniformLocation(const std::string& uniformName) {
    return rlShader.GetShaderLocation(shader, uniformName.c_str());
}

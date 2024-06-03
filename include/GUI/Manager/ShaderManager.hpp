/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ShaderManager
*/

#ifndef SHADERMANAGER_HPP_
#define SHADERMANAGER_HPP_

#include <raylib.h>
#include <string>

class ShaderManager {
public:
    ShaderManager(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderManager();

    void UseShader();
    void SetShaderValue(const std::string& uniformName, const void* value, int uniformType);
    Shader GetShader() const;

private:
    Shader shader;
    int GetUniformLocation(const std::string& uniformName);

    std::string vertexPath;
    std::string fragmentPath;
};

#endif // SHADERMANAGER_HPP_


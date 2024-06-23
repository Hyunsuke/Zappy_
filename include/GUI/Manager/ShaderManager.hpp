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
#include "../Wrapper/Raylib/RLShader.hpp"

class ShaderManager {
public:
    ShaderManager(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderManager();

    void UseShader();
    void SetShaderValue(const std::string& uniformName, const Vector3& value, int uniformType);
    Shader GetShader() const;

private:
    Shader shader;
    int GetUniformLocation(const std::string& uniformName);

    std::string vertexPath;
    std::string fragmentPath;
    RLShader rlShader;
};

#endif // SHADERMANAGER_HPP_


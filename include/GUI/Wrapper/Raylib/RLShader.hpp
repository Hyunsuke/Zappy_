/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLShader
*/

#ifndef RLSHADER_HPP_
#define RLSHADER_HPP_

#include "raylib.h"
#include <string>

class RLShader {
public:
    RLShader(const std::string& vertexPath, const std::string& fragmentPath);
    ~RLShader();

    Shader GetShader() const;
    void SetShaderValue(const std::string& uniformName, const void* value, int uniformType);

private:
    Shader shader;
};

#endif // RLSHADER_HPP_


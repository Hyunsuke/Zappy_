/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLShader
*/

#ifndef RLSHADER_HPP_
#define RLSHADER_HPP_

#include <raylib.h>
#include <string>

class RLShader {
public:
    static Shader LoadShader(const std::string& vsFileName, const std::string& fsFileName);
    static void UnloadShader(Shader shader);
    static void BeginShaderMode(Shader shader);
    static void SetShaderValue(Shader shader, int uniformLoc, const Vector3& value, int uniformType);
    static int GetShaderLocation(Shader shader, const std::string& uniformName);
};

#endif // RLSHADER_HPP_


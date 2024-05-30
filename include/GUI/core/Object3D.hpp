/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Object3D
*/

#ifndef OBJECT3D_HPP_
#define OBJECT3D_HPP_

#include "ModelLoader.hpp"

class Object3D {
public:
    Object3D(const Vector3& position, const std::string& modelPath, const std::string& texturePath, float scale = 1.0f, Vector3 rotationAxis = {0.0f, 1.0f, 0.0f}, float rotationAngle = 0.0f);
    ~Object3D();

    void Draw();
    void Move(Vector3 newPosition);
    void SetScale(float scale);
    float GetScale() const;
    void SetRotation(Vector3 rotationAxis, float rotationAngle);
    Vector3 GetRotationAxis() const;
    float GetRotationAngle() const;
    Vector3 GetPosition() const;
    void SetActive(bool active);
    bool IsActive() const;
    void SetShader(const Shader& shader);
    BoundingBox GetBoundingBox() const;
    Model GetModel() const;

private:
    Vector3 position;
    ModelLoader modelLoader;
    bool active;
    Shader shader;
    float scale;
    Vector3 rotationAxis;
    float rotationAngle;
};

#endif // OBJECT3D_HPP_

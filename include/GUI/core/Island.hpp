/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Island
*/

#ifndef ISLAND_HPP_
#define ISLAND_HPP_

#include "Object3D.hpp"
#include <vector>
#include <memory>
#include "../Utils/utils.hpp"
#include "Egg.hpp"
#include "../Wrapper/Raylib/RLModel.hpp"

class Player;

class Island {
public:
    Island(int x, int y, const Vector3& position, const std::string& modelPath, const std::string& texturePath, float scale = 1.0f, Vector3 rotationAxis = {0.0f, 1.0f, 0.0f}, float rotationAngle = 0.0f);
    ~Island();
    void Draw();
    void DrawWires();
    void Move(Vector3 newPosition);
    void SetScale(float scale);
    float GetScale() const;
    void SetRotation(Vector3 rotationAxis, float rotationAngle);
    Vector3 GetRotationAxis() const;
    float GetRotationAngle() const;
    void AddObject(std::shared_ptr<Object3D> object);
    Vector3 GetPosition() const;
    int GetX() const;
    int GetY() const;
    BoundingBox GetBoundingBox() const;
    std::vector<std::shared_ptr<Object3D>> GetObjects() const;
    std::shared_ptr<Model> GetModel() const;
    void SetShader(const Shader& shader);

    std::shared_ptr<Object3D> food;
    std::shared_ptr<Object3D> linemate;
    std::shared_ptr<Object3D> deraumere;
    std::shared_ptr<Object3D> sibur;
    std::shared_ptr<Object3D> mendiane;
    std::shared_ptr<Object3D> phiras;
    std::shared_ptr<Object3D> thystame;

    std::vector<std::shared_ptr<Player>> GetPlayers();
    void AddPlayer(std::shared_ptr<Player> player);
    void RemovePlayer(std::shared_ptr<Player> player);

    void AddEgg(std::shared_ptr<Egg> egg);
    void RemoveEgg(int eggId);
    std::vector<std::shared_ptr<Egg>> GetEggs() const;
    Vector3 GetEggPosition() const;

private:
    int x, y;
    Vector3 position;
    ModelLoader modelLoader;
    std::vector<std::shared_ptr<Object3D>> objects;
    Shader shader;
    float scale;
    Vector3 rotationAxis;
    float rotationAngle;
    float floatOffset;
    float floatSpeed;
    float baseY;
    float thystameAngle;

    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Egg>> eggs;
    RLModel rlModel;
};

#endif // ISLAND_HPP_

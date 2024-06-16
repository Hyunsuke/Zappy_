/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#ifndef EGG_HPP_
#define EGG_HPP_

#include "Object3D.hpp"
#include <memory>
#include "../Utils/utils.hpp"
#include "ModelLoader.hpp"

class Egg  {
public:
    Egg(int id, int playerNumber);
    ~Egg();

    int GetId() const;
    int GetPlayerNumber() const;
    std::shared_ptr<Model> GetModel() const;

private:
    int id;
    int playerNumber;
    ModelLoader modelLoader;
};

#endif // EGG_HPP_

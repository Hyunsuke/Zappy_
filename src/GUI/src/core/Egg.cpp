/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#include "gui.hpp"

Egg::Egg(int id, int playerNumber)
    : id(id), playerNumber(playerNumber),
    modelLoader("src/GUI/assets/Egg/egg.obj"){
    modelLoader.SetTexture("src/GUI/assets/Egg/egg.png");
}

Egg::~Egg() {}

int Egg::GetId() const {
    return id;
}

int Egg::GetPlayerNumber() const {
    return playerNumber;
}

std::shared_ptr<Model> Egg::GetModel() const {
    return modelLoader.GetModel();
}

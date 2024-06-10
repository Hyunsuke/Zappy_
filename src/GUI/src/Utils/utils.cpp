/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** utils.cpp
*/

#include "gui.hpp"

std::string Utils::GetAssetPath()
{
    return "src/GUI/assets";
}

void Utils::removeDuplicates(std::vector<std::string>& vec) {
    std::set<std::string> uniqueElements;
    std::vector<std::string> result;

    for (const auto& element : vec) {
        if (uniqueElements.find(element) == uniqueElements.end()) {
            uniqueElements.insert(element);
            result.push_back(element);
        }
    }

    vec = std::move(result);
}
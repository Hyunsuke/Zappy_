/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>

class Utils {
    public:
        std::string GetAssetPath();
        static void removeDuplicates(std::vector<std::string>& vec);
};

#endif /* !UTILS_HPP_ */
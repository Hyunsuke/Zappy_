/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** LoadingMenu
*/

#ifndef LOADING_MENU_HPP
#define LOADING_MENU_HPP

#include <string>

class LoadingMenu {
public:
    LoadingMenu(int screenWidth, int screenHeight);
    void Draw();
private:
    int screenWidth;
    int screenHeight;
    Camera camera;
    Sky sky;
    std::shared_ptr<Texture2D> image;
    std::shared_ptr<Texture2D> imageStudio;
    RLText rlText;
    RLWindow window;
    RLModel rlmodel;
};

#endif // LOADING_MENU_HPP

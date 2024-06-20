#ifndef LOADING_MENU_HPP
#define LOADING_MENU_HPP

#include <string>

class LoadingMenu {
public:
    LoadingMenu(int screenWidth, int screenHeight);
    ~LoadingMenu();
    void Draw();
private:
    int screenWidth;
    int screenHeight;
    Camera camera;
    Sky sky;
    Texture2D image;
    Texture2D imageStudio;
};

#endif // LOADING_MENU_HPP

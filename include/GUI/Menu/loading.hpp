#ifndef LOADINGSCREEN_HPP
#define LOADINGSCREEN_HPP

#include "../core/CameraController.hpp"
#include "../Sky/Sky.hpp"

#include <string>
#include <raylib.h>

class LoadingScreen {
public:
    LoadingScreen(int screenWidth, int screenHeight);
    ~LoadingScreen();
    void Draw(const std::string& message, float progress);
private:
    int screenWidth;
    int screenHeight;
    Camera camera;
    Sky sky;
    Texture2D image;
};

#endif // LOADINGSCREEN_HPP

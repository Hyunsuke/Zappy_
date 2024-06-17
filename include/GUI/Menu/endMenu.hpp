#ifndef ENDMENU_HPP
#define ENDMENU_HPP

#include "../Sky/Sky.hpp"
#include "../core/CameraController.hpp"

#include "raylib.h"
#include <string>

class EndMenu {
public:
    EndMenu(int screenWidth, int screenHeight);
    void Draw(const std::string& winningTeam);
    void HandleMouseInput(Vector2 mousePosition);

private:
    int screenWidth;
    int screenHeight;
    Camera camera;
    Sky sky;

    bool closeButtonClicked;

    bool IsMouseOverButton(Rectangle button);
};

#endif // ENDMENU_HPP

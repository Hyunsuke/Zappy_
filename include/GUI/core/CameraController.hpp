/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** CameraController
*/

#ifndef CAMERACONTROLLER_HPP_
#define CAMERACONTROLLER_HPP_

#include "raylib.h"

class CameraController {
public:
    CameraController();
    void Update();
    Camera GetCamera() const;

private:
    Camera camera;
};

#endif /* !CAMERACONTROLLER_HPP_ */

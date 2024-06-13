/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sky
*/

#ifndef SKY_HPP_
#define SKY_HPP_

#include <raylib.h>
#include <cmath>

class Sky {
public:
    Sky(int screenWidth, int screenHeight);
    ~Sky();

    void Update();
    void DrawBackground();
    void DrawSunAndMoon();
    Vector3 GetLightPosition() const;
    Vector3 GetLightColor();
    void OnWindowResized(int newScreenWidth, int newScreenHeight); // Nouvelle méthode

private:
    int screenWidth;
    int screenHeight;

    Vector3 sunPosition;
    Vector3 moonPosition;
    Vector3 lightPosition;
    Color lightColor;

    float dayDuration;
    float currentTime;

    Color ColorLerp(Color start, Color end, float amount);
    Vector3 ColorToVector3(Color color);
};

#endif // SKY_HPP_

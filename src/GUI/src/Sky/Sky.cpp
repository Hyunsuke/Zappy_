/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sky
*/

#include "gui.hpp"

Sky::Sky(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      sunPosition({0.0f, 100.0f, 0.0f}), moonPosition({0.0f, -100.0f, 0.0f}),
      lightPosition(sunPosition), lightColor(WHITE),
      dayDuration(170.0f), currentTime(0.0f), timeUnitFactor(1.0f) {}

Sky::~Sky() {}

void Sky::Update(int timeUnit) {
    timeUnitFactor = static_cast<float>(timeUnit) / 60.0f;

    currentTime += rltext.GetFrameTime() * timeUnitFactor;
    if (currentTime > dayDuration) {
        currentTime -= dayDuration;
    }

    float timeRatio = currentTime / dayDuration;
    float angle = timeRatio * 2.0f * PI;

    sunPosition.x = 200.0f * std::cos(angle);
    sunPosition.z = 100.0f * std::sin(angle);
    sunPosition.y = 100.0f * std::sin(angle);

    moonPosition.x = 200.0f * std::cos(angle + PI);
    moonPosition.z = 100.0f * std::sin(angle + PI);
    moonPosition.y = 100.0f * std::sin(angle + PI);

    if (sunPosition.y > 0) {
        lightPosition = sunPosition;
        lightColor = ColorLerp(YELLOW, WHITE, sunPosition.y / 100.0f);
    } else {
        lightPosition = moonPosition;
        lightColor = ColorLerp(BLUE, WHITE, moonPosition.y / 100.0f);
    }
}

void Sky::DrawBackground() {
    Color startColor, endColor;
    float dayFactor = sunPosition.y / 100.0f;

    if (sunPosition.y > 0) {
        startColor = ColorLerp(ORANGE, SKYBLUE, dayFactor);
        endColor = ColorLerp(DARKBLUE, BLUE, dayFactor);
    } else {
        float nightFactor = (moonPosition.y + 100.0f) / 200.0f;
        startColor = ColorLerp(DARKBLUE, BLACK, nightFactor);
        endColor = ColorLerp(BLACK, DARKBLUE, nightFactor);
    }

    for (int y = 0; y < (screenHeight + 1); y++) {
        float t = (float)y / (float)screenHeight;
        Color color = ColorLerp(startColor, endColor, t);
        rltext.DrawLine(0, y, screenWidth, y, color);
    }
}

void Sky::DrawSunAndMoon() {
    if (sunPosition.y > 0) {
        rltext.DrawSphere(sunPosition, 5.0f, YELLOW);
    } else {
        rltext.DrawSphere(moonPosition, 5.0f, BLUE);
    }
}

Vector3 Sky::GetLightPosition() const {
    return lightPosition;
}

Vector3 Sky::GetLightColor() {
    return ColorToVector3(lightColor);
}

Color Sky::ColorLerp(Color start, Color end, float amount) {
    Color result;
    result.r = start.r + amount * (end.r - start.r);
    result.g = start.g + amount * (end.g - start.g);
    result.b = start.b + amount * (end.b - start.b);
    result.a = start.a + amount * (end.a - start.a);
    return result;
}

Vector3 Sky::ColorToVector3(Color color) {
    return { (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f };
}

void Sky::OnWindowResized(int newScreenWidth, int newScreenHeight) {
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
}

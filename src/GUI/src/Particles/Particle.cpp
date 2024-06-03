/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Particle
*/

#include "gui.hpp"

Particle::Particle(Vector3 position, Vector3 velocity, float lifespan, Color color)
    : position(position), velocity(velocity), lifespan(lifespan), age(0.0f), color(color), size(0.5f) {}

void Particle::Update(float deltaTime) {
    age += deltaTime;
    if (age < lifespan) {
        position = Vector3Add(position, Vector3Scale(velocity, deltaTime));
        color.a = (unsigned char)(255 * (1.0f - age / lifespan));
        size = 0.2f + age * 0.2f; // Particles grow in size over time
    }
}

void Particle::Draw() const {
    if (IsAlive()) {
        DrawSphere(position, size, color); // Corrected particle drawing
    }
}

bool Particle::IsAlive() const {
    return age < lifespan;
}
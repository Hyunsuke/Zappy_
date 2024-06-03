/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Particle
*/

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <raylib.h>

class Particle {
public:
    Particle(Vector3 position, Vector3 velocity, float lifespan, Color color);
    ~Particle() {}

    void Update(float deltaTime);
    void Draw() const;
    bool IsAlive() const;

private:
    Vector3 position;
    Vector3 velocity;
    float lifespan;
    float age;
    Color color;
    float size;
};

#endif // PARTICLE_HPP_


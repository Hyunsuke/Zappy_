/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParticleSystem
*/

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include "Particle.hpp"
#include <vector>
#include <algorithm>

class ParticleSystem {
public:
    ParticleSystem(Vector3 position);
    ~ParticleSystem() {}

    void Update(float deltaTime);
    void Draw() const;
    void Emit(int count);

private:
    Vector3 position;
    std::vector<Particle> particles;
};

#endif // PARTICLESYSTEM_HPP_

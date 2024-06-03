/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ParticleSystem
*/

#include "gui.hpp"

ParticleSystem::ParticleSystem(Vector3 position)
    : position(position) {}

void ParticleSystem::Update(float deltaTime) {
    for (auto& particle : particles) {
        particle.Update(deltaTime);
    }
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return !p.IsAlive(); }), particles.end());
}

void ParticleSystem::Draw() const {
    for (const auto& particle : particles) {
        particle.Draw();
    }
}

void ParticleSystem::Emit(int count) {
    for (int i = 0; i < count; ++i) {
        Vector3 velocity = { (float)(rand() % 100 - 50) / 200.0f, (float)(rand() % 100 + 100) / 100.0f, (float)(rand() % 100 - 50) / 200.0f };
        float lifespan = 1.0f + (float)(rand() % 100) / 100.0f;
        Color color = RED;
        particles.emplace_back(position, velocity, lifespan, color);
    }
}

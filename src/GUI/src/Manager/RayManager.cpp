/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RayManager
*/

#include "gui.hpp"

RayManager::RayManager() {}

void RayManager::UpdateRay(Camera camera) {
    ray = GetMouseRay(GetMousePosition(), camera);
}

std::shared_ptr<Island> RayManager::GetIslandUnderMouse(const std::vector<std::shared_ptr<Island>>& islands) {
    for (auto& island : islands) {
        Matrix transform = MatrixTranslate(island->GetPosition().x, island->GetPosition().y, island->GetPosition().z);
        if (CheckRayCollisionModel(ray, *island->GetModel(), transform)) {
            return island;
        }
    }
    return nullptr;
}

std::shared_ptr<Player> RayManager::GetPlayerUnderMouse(const std::vector<std::shared_ptr<Player>>& players) {
    for (auto& player : players) {
        Matrix transform = MatrixTranslate(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
        if (CheckRayCollisionModel(ray, *player->GetModel(), transform)) {
            return player;
        }
    }
    return nullptr;
}

bool CheckCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3* outCollisionPoint) {
    Vector3 edge1 = Vector3Subtract(p2, p1);
    Vector3 edge2 = Vector3Subtract(p3, p1);
    Vector3 pvec = Vector3CrossProduct(ray.direction, edge2);
    float det = Vector3DotProduct(edge1, pvec);

    if (det > -0.0001f && det < 0.0001f) return false;
    float invDet = 1.0f / det;

    Vector3 tvec = Vector3Subtract(ray.position, p1);
    float u = Vector3DotProduct(tvec, pvec) * invDet;
    if (u < 0.0f || u > 1.0f) return false;

    Vector3 qvec = Vector3CrossProduct(tvec, edge1);
    float v = Vector3DotProduct(ray.direction, qvec) * invDet;
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = Vector3DotProduct(edge2, qvec) * invDet;
    if (t > 0) {
        if (outCollisionPoint) *outCollisionPoint = Vector3Add(ray.position, Vector3Scale(ray.direction, t));
        return true;
    }

    return false;
}

bool RayManager::CheckRayCollisionModel(Ray ray, const Model& model, const Matrix& transform) {
    for (int i = 0; i < model.meshCount; i++) {
        Mesh mesh = model.meshes[i];
        for (int j = 0; j < mesh.triangleCount; j++) {
            Vector3 v0 = Vector3Transform(Vector3{mesh.vertices[j * 9 + 0], mesh.vertices[j * 9 + 1], mesh.vertices[j * 9 + 2]}, transform);
            Vector3 v1 = Vector3Transform(Vector3{mesh.vertices[j * 9 + 3], mesh.vertices[j * 9 + 4], mesh.vertices[j * 9 + 5]}, transform);
            Vector3 v2 = Vector3Transform(Vector3{mesh.vertices[j * 9 + 6], mesh.vertices[j * 9 + 7], mesh.vertices[j * 9 + 8]}, transform);

            if (CheckCollisionRayTriangle(ray, v0, v1, v2, nullptr)) {
                return true;
            }
        }
    }
    return false;
}

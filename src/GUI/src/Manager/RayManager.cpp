/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RayManager
*/

#include "gui.hpp"

RayManager::RayManager() {}

void RayManager::UpdateRay(Camera camera) {
    ray = rlModel.GetMouseRay(rlModel.GetMousePosition(), camera);
}

std::shared_ptr<Island> RayManager::GetIslandUnderMouse(const std::vector<std::shared_ptr<Island>>& islands) {
    for (auto& island : islands) {
        Matrix transform = rlModel.MatrixTranslate(island->GetPosition().x, island->GetPosition().y, island->GetPosition().z);
        if (CheckRayCollisionModel(ray, island->GetModel(), transform)) {
            return island;
        }
    }
    return nullptr;
}

std::shared_ptr<Player> RayManager::GetPlayerUnderMouse(const std::vector<std::shared_ptr<Player>>& players) {
    for (auto& player : players) {
        BoundingBox playerBoundingBox = rlModel.GetModelBoundingBox(player->GetModel());
        Vector3 scale = player->GetScale();
        Matrix transform = rlModel.MatrixMultiply(rlModel.MatrixScale(scale.x, scale.y, scale.z), rlModel.MatrixTranslate(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z));
        playerBoundingBox.min = rlModel.Vector3Transform(playerBoundingBox.min, transform);
        playerBoundingBox.max = rlModel.Vector3Transform(playerBoundingBox.max, transform);

        if (CheckCollisionRayBox(ray, playerBoundingBox)) {
            return player;
        }
    }
    return nullptr;
}

bool RayManager::CheckCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, std::shared_ptr<Vector3> outCollisionPoint) {
    Vector3 edge1 = rlModel.Vector3Subtract(p2, p1);
    Vector3 edge2 = rlModel.Vector3Subtract(p3, p1);
    Vector3 pvec = rlModel.Vector3CrossProduct(ray.direction, edge2);
    float det = rlModel.Vector3DotProduct(edge1, pvec);

    if (det > -0.0001f && det < 0.0001f) return false;
    float invDet = 1.0f / det;

    Vector3 tvec = rlModel.Vector3Subtract(ray.position, p1);
    float u = rlModel.Vector3DotProduct(tvec, pvec) * invDet;
    if (u < 0.0f || u > 1.0f) return false;

    Vector3 qvec = rlModel.Vector3CrossProduct(tvec, edge1);
    float v = rlModel.Vector3DotProduct(ray.direction, qvec) * invDet;
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = rlModel.Vector3DotProduct(edge2, qvec) * invDet;
    if (t > 0) {
        if (outCollisionPoint) outCollisionPoint = rlModel.Vector3AddReturnShared(ray.position, rlModel.Vector3Scale(ray.direction, t));
        return true;
    }

    return false;
}

bool RayManager::CheckRayCollisionModel(Ray ray, std::shared_ptr<Model> model, const Matrix& transform) {
    for (int i = 0; i < model->meshCount; i++) {
        Mesh mesh = model->meshes[i];
        int vertexCount = mesh.vertexCount;

        for (int j = 0; j < mesh.triangleCount; j++) {
            int index0 = j * 9 + 0;
            int index1 = j * 9 + 3;
            int index2 = j * 9 + 6;

            if (index0 < vertexCount * 3 && index1 < vertexCount * 3 && index2 < vertexCount * 3) {
                Vector3 v0 = rlModel.Vector3Transform(Vector3{mesh.vertices[index0], mesh.vertices[index0 + 1], mesh.vertices[index0 + 2]}, transform);
                Vector3 v1 = rlModel.Vector3Transform(Vector3{mesh.vertices[index1], mesh.vertices[index1 + 1], mesh.vertices[index1 + 2]}, transform);
                Vector3 v2 = rlModel.Vector3Transform(Vector3{mesh.vertices[index2], mesh.vertices[index2 + 1], mesh.vertices[index2 + 2]}, transform);

                if (CheckCollisionRayTriangle(ray, v0, v1, v2, nullptr)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool RayManager::CheckCollisionRayBox(Ray ray, BoundingBox box) {
    Vector3 dirfrac = {};
    dirfrac.x = 1.0f / ray.direction.x;
    dirfrac.y = 1.0f / ray.direction.y;
    dirfrac.z = 1.0f / ray.direction.z;

    Vector3 lb = box.min;
    Vector3 rt = box.max;

    float t1 = (lb.x - ray.position.x) * dirfrac.x;
    float t2 = (rt.x - ray.position.x) * dirfrac.x;
    float t3 = (lb.y - ray.position.y) * dirfrac.y;
    float t4 = (rt.y - ray.position.y) * dirfrac.y;
    float t5 = (lb.z - ray.position.z) * dirfrac.z;
    float t6 = (rt.z - ray.position.z) * dirfrac.z;

    float tmin = std::max({std::min(t1, t2), std::min(t3, t4), std::min(t5, t6)});
    float tmax = std::min({std::max(t1, t2), std::max(t3, t4), std::max(t5, t6)});

    if (tmax < 0 || tmin > tmax) {
        return false;
    }

    return true;
}
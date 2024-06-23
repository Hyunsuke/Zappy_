/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLModel
*/

#ifndef RLMODEL_HPP_
#define RLMODEL_HPP_

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <memory>

class RLModel {
public:
    static Model LoadModel(const std::string& filePath);
    static void UnloadModel(std::shared_ptr<Model> model);
    static Texture2D LoadTexture(const std::string& filePath);
    static void UnloadTexture(std::shared_ptr<Texture2D> texture);
    static void DrawTextureEx(std::shared_ptr<Texture2D> texture, Vector2 position, float rotation, float scale, Color tint);

    static void DrawModelEx(std::shared_ptr<Model> model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
    static void SetLineWidth(float width);
    static void DrawModelWiresEx(std::shared_ptr<Model> model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
    static void DrawModel(std::shared_ptr<Model> model, Vector3 position, float scale, Color tint);

    static float GetFrameTime();
    static double GetTime();

    static void UpdateModelAnimation(std::shared_ptr<Model> model, std::shared_ptr<ModelAnimation> anim, int frame);
    static Vector3 Vector3Lerp(Vector3 start, Vector3 end, float amount);
    static Vector3 Vector3Add(Vector3 v1, Vector3 v2);
    static Vector3 Vector3Normalize(Vector3 v);
    static Vector3 Vector3Subtract(Vector3 v1, Vector3 v2);
    static Matrix MatrixRotate(Vector3 axis, float angle);
    static Vector3 Vector3Transform(Vector3 v, Matrix mat);
    static Vector3 Vector3CrossProduct(Vector3 v1, Vector3 v2);
    static Vector3 Vector3Scale(Vector3 v, float scale);
    static float Vector3DotProduct(Vector3 v1, Vector3 v2);
    static std::shared_ptr<Vector3> Vector3AddReturnShared(Vector3 v1, Vector3 v2);

    static Vector2 GetMousePosition();
    static bool IsMouseButtonDown(int button);
    static bool IsMouseButtonPressed(int button);
    static bool IsKeyDown(int key);

    static void SetMaterialTexture(Material& material, int mapType, std::shared_ptr<Texture2D> texture);

    static BoundingBox GetModelBoundingBox(std::shared_ptr<Model> model);
    static Matrix MatrixTranslate(float x, float y, float z);
    static Matrix MatrixMultiply(Matrix left, Matrix right);
    static Matrix MatrixScale(float x, float y, float z);
    static Ray GetMouseRay(Vector2 mousePosition, Camera camera);
    static float Vector3Distance(Vector3 v1, Vector3 v2);
};

#endif // RLMODEL_HPP_


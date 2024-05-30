/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Island
*/

#include "gui.hpp"

Island::Island(int id, const Vector3& position, const std::string& modelPath, const std::string& texturePath, float scale, Vector3 rotationAxis, float rotationAngle)
    : id(id), position(position), modelLoader(modelPath), scale(scale), rotationAxis(rotationAxis), rotationAngle(rotationAngle) {
    modelLoader.SetTexture(texturePath);

    float objectScale = 0.01f;

    food = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    linemate = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    deraumere = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    sibur = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    mendiane = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    phiras = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    thystame = std::make_shared<Object3D>(Vector3{0.0f, 0.0f, 0.0f}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);

    objects.push_back(food);
    objects.push_back(linemate);
    objects.push_back(deraumere);
    objects.push_back(sibur);
    objects.push_back(mendiane);
    objects.push_back(phiras);
    objects.push_back(thystame);
}

Island::~Island() {}

void Island::Draw() {
    modelLoader.Draw(position, scale, rotationAxis, rotationAngle, WHITE);
    for (auto& obj : objects) {
        if (obj->GetQuantity() > 0) {
            obj->Draw();
        }
    }
}

void Island::Move(Vector3 newPosition) {
    Vector3 delta = Vector3Subtract(newPosition, position);
    position = newPosition;
    for (auto& obj : objects) {
        obj->Move(Vector3Add(obj->GetPosition(), delta));
    }
}

void Island::SetScale(float scale) {
    this->scale = scale;
    for (auto& obj : objects) {
        obj->SetScale(scale);
    }
}

float Island::GetScale() const {
    return scale;
}

void Island::SetRotation(Vector3 rotationAxis, float rotationAngle) {
    this->rotationAxis = rotationAxis;
    this->rotationAngle = rotationAngle;
    for (auto& obj : objects) {
        obj->SetRotation(rotationAxis, rotationAngle);
    }
}

Vector3 Island::GetRotationAxis() const {
    return rotationAxis;
}

float Island::GetRotationAngle() const {
    return rotationAngle;
}

void Island::AddObject(std::shared_ptr<Object3D> object) {
    objects.push_back(object);
}

Vector3 Island::GetPosition() const {
    return position;
}

int Island::GetId() const {
    return id;
}

BoundingBox Island::GetBoundingBox() const {
    return modelLoader.GetBoundingBox();
}

std::vector<std::shared_ptr<Object3D>> Island::GetObjects() const {
    return objects;
}

Model Island::GetModel() const {
    return modelLoader.GetModel();
}

void Island::SetShader(const Shader& shader) {
    this->shader = shader;
    modelLoader.SetShader(shader);
    for (auto& obj : objects) {
        obj->SetShader(shader);
    }
}
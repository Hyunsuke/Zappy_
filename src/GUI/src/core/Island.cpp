/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Island
*/

#include "gui.hpp"

Island::Island(int x, int y, const Vector3& position, const std::string& modelPath, const std::string& texturePath, float scale, Vector3 rotationAxis, float rotationAngle)
    : x(x), y(y), position(position), modelLoader(modelPath), scale(scale), rotationAxis(rotationAxis), rotationAngle(rotationAngle), floatSpeed((rand() % 100) / 50.0f + 1.0f), baseY(position.y) {
    modelLoader.SetTexture(texturePath);

    float objectScale = 0.01f;
    float linemateScale = 0.1f;
    float deramereScale = 1.0f;
    Vector3 deramereRotationAxis = {1.0f, 0.0f, 0.0f};
    float deramereRotationAngle = 45.0f;
    float siburScale = 0.5f;
    Vector3 siburrotationAxis = {1.0f, 0.0f, 0.0f};
    float siburrotationAngle = 25.0f;

    food = std::make_shared<Object3D>(Vector3{position.x, position.y + 10.0f, position.z}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    linemate = std::make_shared<Object3D>(Vector3{position.x + 1.9f, position.y + 1.0f, position.z - 0.2f}, "src/GUI/assets/Linemate/Linemate.obj", "src/GUI/assets/Linemate/Linemate.png", linemateScale, rotationAxis, rotationAngle);
    deraumere = std::make_shared<Object3D>(Vector3{position.x - 3.5f, position.y + 0.6f, position.z + 0.3f}, "src/GUI/assets/Deraumere/deraumere.obj", "src/GUI/assets/Deraumere/deraumere.png", deramereScale, deramereRotationAxis, deramereRotationAngle);
    sibur = std::make_shared<Object3D>(Vector3{position.x + 3.5f, position.y + 2.0f, position.z - 0.3f}, "src/GUI/assets/Sibur/Sword.obj", "src/GUI/assets/Sibur/Sword.png", siburScale, siburrotationAxis, siburrotationAngle);
    mendiane = std::make_shared<Object3D>(Vector3{position.x, position.y + 10.0f, position.z}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    phiras = std::make_shared<Object3D>(Vector3{position.x, position.y + 10.0f, position.z}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);
    thystame = std::make_shared<Object3D>(Vector3{position.x, position.y + 10.0f, position.z}, "src/GUI/assets/duck/RubberDuck_LOD0.obj", "src/GUI/assets/duck/duck_text.png", objectScale, rotationAxis, rotationAngle);

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

int Island::GetX() const {
    return x;
}

int Island::GetY() const {
    return y;
}

BoundingBox Island::GetBoundingBox() const {
    return modelLoader.GetBoundingBox();
}

std::vector<std::shared_ptr<Object3D>> Island::GetObjects() const {
    return objects;
}

std::shared_ptr<Model> Island::GetModel() const {
    return modelLoader.GetModel();
}

void Island::SetShader(const Shader& shader) {
    this->shader = shader;
    modelLoader.SetShader(shader);
    for (auto& obj : objects) {
        obj->SetShader(shader);
    }
}
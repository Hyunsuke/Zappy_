/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Island
*/

#include "gui.hpp"

Island::Island(int x, int y, const Vector3& position, const std::string& modelPath, const std::string& texturePath, float scale, Vector3 rotationAxis, float rotationAngle)
    : x(x), y(y), position(position), modelLoader(modelPath), scale(scale), rotationAxis(rotationAxis), rotationAngle(rotationAngle), floatSpeed((rand() % 100) / 50.0f + 1.0f), baseY(position.y), thystameAngle(0.0f) {
    modelLoader.SetTexture(texturePath);

    float foodScale = 0.025f;
    Vector3 foodRotationAxis = {0.0f, 1.0f, 0.0f};
    float foodRotationAngle = -50.0f;
    float linemateScale = 0.1f;
    float deramereScale = 1.0f;
    Vector3 deramereRotationAxis = {1.0f, 0.0f, 0.0f};
    float deramereRotationAngle = 45.0f;
    float siburScale = 0.5f;
    Vector3 siburrotationAxis = {1.0f, 0.0f, 0.0f};
    float siburrotationAngle = 25.0f;
    float mendianeScale = 0.03f;
    Vector3 mendianeRotationAxis = {1.0f, 0.0f, 0.0f};
    float mendianeRotationAngle = 40.0f;
    float phirasScale = 6.0f;
    Vector3 phirasRotationAxis = {0.0f, 1.0f, 0.0f};
    float phirasRotationAngle = -35.0f;
    float thystameScale = 0.00015f;

    food = std::make_shared<Object3D>(Vector3{position.x - 4.0f, position.y + 0.15f, position.z + 2.0f}, "src/GUI/assets/Food/pig.obj", "src/GUI/assets/Food/pig.png", foodScale, foodRotationAxis, foodRotationAngle);
    linemate = std::make_shared<Object3D>(Vector3{position.x + 1.9f, position.y + 1.0f, position.z - 0.2f}, "src/GUI/assets/Linemate/Linemate.obj", "src/GUI/assets/Linemate/Linemate.png", linemateScale, rotationAxis, rotationAngle);
    deraumere = std::make_shared<Object3D>(Vector3{position.x - 3.5f, position.y + 0.6f, position.z + 0.3f}, "src/GUI/assets/Deraumere/deraumere.obj", "src/GUI/assets/Deraumere/deraumere.png", deramereScale, deramereRotationAxis, deramereRotationAngle);
    sibur = std::make_shared<Object3D>(Vector3{position.x + 3.5f, position.y + 2.0f, position.z - 0.3f}, "src/GUI/assets/Sibur/Sword.obj", "src/GUI/assets/Sibur/Sword.png", siburScale, siburrotationAxis, siburrotationAngle);
    mendiane = std::make_shared<Object3D>(Vector3{position.x - 0.3f, position.y + 1.3f, position.z + 0.3f}, "src/GUI/assets/Mendiane/mendiane.obj", "src/GUI/assets/Mendiane/mendiane.png", mendianeScale, mendianeRotationAxis, mendianeRotationAngle);
    phiras = std::make_shared<Object3D>(Vector3{position.x - 1.8f, position.y + 3.10f, position.z}, "src/GUI/assets/Phiras/phiras.obj", "src/GUI/assets/Phiras/phiras.png", phirasScale, phirasRotationAxis, phirasRotationAngle);
    thystame = std::make_shared<Object3D>(Vector3{position.x, position.y + 5.0f, position.z}, "src/GUI/assets/Thystame/thystame.obj", "src/GUI/assets/Thystame/thystame.png", thystameScale, rotationAxis, rotationAngle);

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
    for (auto& egg: eggs) {
        rlModel.DrawModelEx(egg->GetModel(), GetEggPosition(), {0.0f, 0.0f, 0.0f}, 0.0f, {0.4f, 0.4f, 0.4f}, WHITE);
    }
}

void Island::DrawWires() {
    modelLoader.DrawWires(position, scale, rotationAxis, rotationAngle, WHITE);
    for (auto& obj : objects) {
        if (obj->GetQuantity() > 0) {
            obj->DrawWires();
        }
    }
    for (auto& egg: eggs) {
        rlModel.DrawModelWiresEx(egg->GetModel(), GetEggPosition(), {0.0f, 0.0f, 0.0f}, 0.0f, {0.4f, 0.4f, 0.4f}, WHITE);
    }
}

void Island::Move(Vector3 newPosition) {
    Vector3 delta = rlModel.Vector3Subtract(newPosition, position);
    position = newPosition;
    for (auto& obj : objects) {
        if (obj == thystame) {
            thystameAngle += 0.01f;
            float distance = 5.0f;
            Vector3 thystamePos = {
                position.x + distance * std::cos(thystameAngle),
                position.y + 5.0f,
                position.z + distance * std::sin(thystameAngle)
            };
            obj->Move(thystamePos);
            Vector3 direction = rlModel.Vector3Normalize(rlModel.Vector3Subtract(position, thystamePos));
            float rotationAngle = std::atan2(direction.z, direction.x) * (180.0f / PI);
            obj->SetRotation({0.0f, 1.0f, 0.0f}, -rotationAngle);
        } else {
            obj->Move(Vector3Add(obj->GetPosition(), delta));
        }
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

std::vector<std::shared_ptr<Player>> Island::GetPlayers() {
    return players;
}

void Island::AddPlayer(std::shared_ptr<Player> player) {
    players.push_back(player);
}

void Island::RemovePlayer(std::shared_ptr<Player> player) {
    players.erase(std::remove(players.begin(), players.end(), player), players.end());
}

void Island::AddEgg(std::shared_ptr<Egg> egg) {
    eggs.push_back(egg);
}

void Island::RemoveEgg(int eggId) {
    eggs.erase(std::remove_if(eggs.begin(), eggs.end(), [eggId](const std::shared_ptr<Egg>& egg) {
        return egg->GetId() == eggId;
    }), eggs.end());
}

std::vector<std::shared_ptr<Egg>> Island::GetEggs() const {
    return eggs;
}

Vector3 Island::GetEggPosition() const {
    return Vector3{position.x + 3.1f, position.y + 0.8f, position.z + 0.5f};
}
#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "raylib.h"
#include <string>
#include <vector>

class ModelLoader {
public:
    ModelLoader(const std::string& filePath);
    ~ModelLoader();
    void Draw(Vector3 position, float scale, Vector3 rotationAxis, float rotationAngle, Color tint);
    void SetShader(Shader shader);
    Model GetModel() const { return model; }
    void SetTexture(const std::string& texturePath);

private:
    Model model;
    Shader shader;
    std::vector<Color> objectColors; // Couleurs des matériaux
};

#endif // MODEL_LOADER_H

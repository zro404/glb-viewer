#pragma once
#include "main.hpp"

class Model
{
public:
    Model(char* path);
    void Draw(Shader& shader);

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
};

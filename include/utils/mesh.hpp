#ifndef MESH_H
#define MESH_H
#include <cstddef>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <utils/shader.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 Position;     // 位置向量
    glm::vec3 Normal;       // 法向量
    glm::vec2 TexCoords;    // 纹理坐标向量
};

struct Texture {
    unsigned int id;        // 纹理id
    std::string type;       // 纹理类型
    aiString path;
};

class Mesh {
public:
    /* 网格数据 */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /* 函数 */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) 
    {
        this->vertices = vertices;
        this->indices  = indices;
        this->textures = textures;

        setupMesh();
    }
    
    void Draw(Shader shader)
    {
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;

        for (unsigned int i = 0; i < textures.size(); i++) 
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        // 绘制网格
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh() 
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // 顶点位置
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // 顶点法向量
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // 顶点纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};


#endif
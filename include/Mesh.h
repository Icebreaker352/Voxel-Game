#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string.h>
#include <VAO.h>
#include <EBO.h>
#include <Camera.h>
#include <TextureArray.h>
#include <glm/gtx/string_cast.hpp>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    VAO VAO;

    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
    Mesh();

    void Draw(Shader &shader, Camera &camera);
};

#endif
#ifndef MESHER_CLASS_H
#define MESHER_CLASS_H

#include <VBO.h>
#include <iostream>
#include <Chunk.h>
#include <glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <typeinfo>
#include <ChunkLoader.h>
#include <ChunkBoundary.h>
#include <Mesh.h>

class ChunkMesher
{
public:
    int size = 16;
    int boundarySize = 1;

    ChunkLoader loader;
 
    ChunkMesher();
    void updateMeshForChunkAt(glm::vec3 chunkCoords);
    void generateMesh(ChunkBoundary chunk, std::vector<Vertex> &vertexOut, std::vector<GLuint> &indexOut);
    void buildFaces(ChunkBoundary chunk, glm::vec3 chunkCoords, std::vector<Vertex> &vertexOut, std::vector<GLuint> &indexOut);
    void addFace(glm::vec3 coords, glm::vec3 normal, GLuint block, std::vector<Vertex> &vertexOut, std::vector<GLuint> &indexOut);
    int chunkIndex(glm::vec3 coords);
    glm::vec3 chunkCoords(int index);
};

#endif
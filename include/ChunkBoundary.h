#ifndef CHUNK_BOUNDARY_CLASS_H
#define CHUNK_BOUNDARY_CLASS_H

#include <Chunk.h>
#include <vector>

class ChunkBoundary : public Chunk
{
public:
    GLuint chunkData[18 * 18 * 18];
    ChunkBoundary(Chunk center, Chunk top, Chunk bottom, Chunk left, Chunk right, Chunk front, Chunk back);
    virtual glm::vec3 globalCoords(glm::vec3 coords);
    virtual BlockType get(glm::vec3 coords);
    virtual BlockType get(int x, int y, int z);
};

#endif
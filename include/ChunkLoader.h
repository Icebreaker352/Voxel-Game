#ifndef CHUNK_LOADER_CLASS_H
#define CHUNK_LOADER_CLASS_H

#include <VBO.h>
#include <iostream>
#include <Chunk.h>
#include <glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/string_cast.hpp>

class ChunkLoader
{
public:
    const int RENDER_DISTANCE = 2;
    std::vector<Chunk> loadedChunks;

    int totalWidth;

    ChunkLoader();
    void genChunksInRenderDist();
    Chunk getChunkAtGlobalCoords(glm::vec3 coords);
    BlockType get(glm::vec3 coords);
    BlockType get(int x, int y, int z);
    int mod(int x, int y);
};

#endif
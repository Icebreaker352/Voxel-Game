#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <iostream>
#include <glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdlib.h>
#include <ctime>
#include <glad/glad.h>
#include <vector>
#include <Mesh.h>

enum BlockType
{
    AIR = 0,
    COBBLESTONE = 1,
    DIAMOND_BLOCK = 2,
    DIAMOND_ORE = 3,
    DIRT = 4,
    GOLD_BLOCK = 5,
    GRASS_BLOCK = 6,
    OAK_LEAVES = 7,
    OAK_LOG = 8,
    OAK_PLANKS = 9,
    STONE = 10,
    BLOCK_TYPE_COUNT
};

struct BlockTraits {
    const char* name;
    bool isOpaque;
};

constexpr BlockTraits blockTraits[BLOCK_TYPE_COUNT] = {
    {"air", false},
    {"cobblestone", true},
    {"diamond_block", true},
    {"diamond_ore", true},
    {"dirt", true},
    {"gold_block", true},
    {"grass_block", true},
    {"oak_leaves", false},
    {"oak_log", true},
    {"oak_planks", false},
    {"stone", true},
};

class Chunk
{
public:
    int chunkX;
    int chunkY;
    int chunkZ;
    int size;
    
    std::vector<Vertex> meshVertices;
    std::vector<GLuint> meshIndices;
    Mesh chunkMesh;
    
    GLuint chunkData[16 * 16 * 16];

    Chunk(int x, int y, int z, bool generateTerrain=true);
    void generateTerrain();
    BlockType get(glm::vec3 coords);
    BlockType get(int x, int y, int z);
    void set(glm::vec3 coords, BlockType block);
    void set(int x, int y, int z, BlockType block);
    int chunkIndex(glm::vec3 coords);
    glm::vec3 chunkCoords(int index);
    glm::vec3 globalCoords(glm::vec3 coords);
    void updateMesh();
};

#endif
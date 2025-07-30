#include <Chunk.h>

Chunk::Chunk(int x, int y, int z, bool generateTerrain)
{
    chunkX = x;
    chunkY = y;
    chunkZ = z;

    this->size = 16;

    if (generateTerrain) { this->generateTerrain(); }
    else {
        for (int i = 0; i < size * size * size; i++)
        {chunkData[i] = BlockType::AIR;}
    }
}
void Chunk::generateTerrain()
{
    int altitude = 15;
    for (int i = 0; i < size * size * size; i++)
    {
        glm::vec3 coords = globalCoords(chunkCoords(i));
        if (coords.y < 5) chunkData[i] = STONE;
        else if (coords.y < 8) chunkData[i] = COBBLESTONE;
        else if (coords.y < altitude) chunkData[i] = DIRT;
        else if (coords.y < altitude+1)
        {
            chunkData[i] = GOLD_BLOCK;
        }   
        else chunkData[i] = AIR;
        if (i == 240) chunkData[i] = AIR;
    }
}
BlockType Chunk::get(glm::vec3 coords)
{
    return static_cast<BlockType>(chunkData[chunkIndex(coords)]);
}
BlockType Chunk::get(int x, int y, int z)
{
    return static_cast<BlockType>(chunkData[chunkIndex(glm::vec3(x, y, z))]);
}
void Chunk::set(glm::vec3 coords, BlockType block)
{
    chunkData[chunkIndex(coords)] = block;
}
void Chunk::set(int x, int y, int z, BlockType block)
{
    chunkData[chunkIndex(glm::vec3(x,y,z))] = block;
}
int Chunk::chunkIndex(glm::vec3 coords)
{
    return coords.x + (coords.y * size) + (coords.z * size * size);
}
glm::vec3 Chunk::chunkCoords(int index)
{
    glm::vec3 coords;
    coords.x = index % size;
    coords.y = int(glm::floor(index/size)) % size;
    coords.z = glm::floor(index / (size * size));
    return coords;
}
glm::vec3 Chunk::globalCoords(glm::vec3 coords)
{
    return float(size) * glm::vec3(chunkX, chunkY, chunkZ) + coords;
}
void Chunk::updateMesh()
{
    chunkMesh = Mesh(meshVertices, meshIndices);
}
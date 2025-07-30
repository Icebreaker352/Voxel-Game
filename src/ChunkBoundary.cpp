#include <ChunkBoundary.h>

ChunkBoundary::ChunkBoundary(Chunk center, Chunk top, Chunk bottom, Chunk left, Chunk right, Chunk front, Chunk back)
    : Chunk(center.chunkX, center.chunkY, center.chunkZ,false)
{
    chunkX = center.chunkX;
    chunkY = center.chunkY;
    chunkZ = center.chunkZ;

    this->size = 18;

    std::vector<GLuint> data;
    data.reserve(5832);
    for (int i = 0; i < 18; i++)
    {
        data.push_back(BlockType::AIR);
    }
    int iB = 3840;
    for (int j = 0; j < 16; j++)
    {
        data.push_back(BlockType::AIR);
        for (int k = 0; k < 16; k++) {
            data.push_back(back.chunkData[iB++]);
        }
        data.push_back(BlockType::AIR);
    }
    for (int i = 0; i < 18; i++)
    {
        data.push_back(BlockType::AIR);
    }
    iB = 240; int iL = 15; int iR = 0;
    int iT = 0; int iC = 0; int iF = 0;
    for (int i = 0; i < 16; i++)
    {
        data.push_back(BlockType::AIR);
        for (int j = 0; j < 16; j++)
        {
            data.push_back(bottom.chunkData[iB++]);
        }
        iB += 241;
        data.push_back(BlockType::AIR);
        for (int j = 0; j < 16; j++)
        {
            data.push_back(left.chunkData[iL]);
            iL += 16;
            for (int k = 0; k < 16; k++) {
                data.push_back(center.chunkData[iC++]);
            }
            data.push_back(right.chunkData[iR]);
            iR += 16;
        }
        data.push_back(BlockType::AIR);
        for (int j = 0; j < 16; j++) {
            data.push_back(top.chunkData[iT++]);
        }
        iT += 241;
        data.push_back(BlockType::AIR);
    }
    for (int i = 0; i < 18; i++)
    {
        data.push_back(BlockType::AIR);
    }
    for (int j = 0; j < 16; j++)
    {
        data.push_back(BlockType::AIR);
        for (int k = 0; k < 16; k++) {
            data.push_back(front.chunkData[iF++]);
        }
        data.push_back(BlockType::AIR);
    }
    for (int i = 0; i < 18; i++)
    {
        data.push_back(BlockType::AIR);
    }
    std::copy(data.begin(), data.end(), chunkData);
}
glm::vec3 ChunkBoundary::globalCoords(glm::vec3 coords)
{
    return float(16) * glm::vec3(chunkX, chunkY, chunkZ) + coords - glm::vec3(1.0f);
}
BlockType ChunkBoundary::get(glm::vec3 coords)
{
    return static_cast<BlockType>(chunkData[this->chunkIndex(coords)]);
}
BlockType ChunkBoundary::get(int x, int y, int z)
{
    if (chunkData[this->chunkIndex(glm::vec3(x,y,z))]>10) return BlockType::AIR;
    return static_cast<BlockType>(chunkData[this->chunkIndex(glm::vec3(x, y, z))]);
}
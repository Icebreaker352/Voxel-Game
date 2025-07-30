#include <ChunkLoader.h>

ChunkLoader::ChunkLoader() {}
void ChunkLoader::genChunksInRenderDist()
{
    totalWidth = 1+(RENDER_DISTANCE*2);
    int numChunks = totalWidth * totalWidth * totalWidth;

    int x = -RENDER_DISTANCE; int y = -RENDER_DISTANCE; int z = -RENDER_DISTANCE;

    for (int i = 0; i < numChunks; i++)
    {
        this->loadedChunks.push_back(Chunk(x,y,z));
        x++;
        if (x >= totalWidth - RENDER_DISTANCE) {
            x = -RENDER_DISTANCE; y++;
            if (y >= totalWidth - RENDER_DISTANCE) {
                y = -RENDER_DISTANCE; z++;
            }
        }
    }

}
Chunk ChunkLoader::getChunkAtGlobalCoords(glm::vec3 coords)
{
    glm::vec3 xyz = glm::floor(coords / 16.0f);
    int index = (xyz.x+RENDER_DISTANCE) + ((xyz.y+RENDER_DISTANCE) * totalWidth) + ((xyz.z+RENDER_DISTANCE) * totalWidth * totalWidth);
    if (abs(xyz.x) > RENDER_DISTANCE || abs(xyz.y) > RENDER_DISTANCE || abs(xyz.z) > RENDER_DISTANCE)
        return Chunk(0,0,0,false);
    try {return loadedChunks.at(index);}
    catch (...) {return Chunk(0,0,0,false);}
}
BlockType ChunkLoader::get(glm::vec3 coords)
{
    Chunk chunk(0,0,0);
    glm::vec3 localCoords = glm::vec3(int(mod(coords.x, 16)), int(mod(coords.y, 16)), int(mod(coords.z, 16)));
    return getChunkAtGlobalCoords(coords).get(localCoords);
}
BlockType ChunkLoader::get(int x, int y, int z)
{
    Chunk chunk(0,0,0);
    glm::vec3 localCoords = glm::vec3(mod(x, 16), mod(y, 16), mod(z, 16));
    return getChunkAtGlobalCoords(glm::vec3(x,y,z)).get(localCoords);
}
int ChunkLoader::mod(int x, int y)
{
    return (x % y + y) % y;
}
#include <ChunkMesher.h>

ChunkMesher::ChunkMesher() {
    loader.genChunksInRenderDist();

    for (int i = 0; i < loader.loadedChunks.size(); i++)
    {
        int x = loader.loadedChunks[i].chunkX * 16.0f;
        int y = loader.loadedChunks[i].chunkY * 16.0f;
        int z = loader.loadedChunks[i].chunkZ * 16.0f;
        ChunkBoundary chunkbounds(loader.loadedChunks[i],
            loader.getChunkAtGlobalCoords(glm::vec3(x, y + 16, z)),
            loader.getChunkAtGlobalCoords(glm::vec3(x, y - 16, z)),
            loader.getChunkAtGlobalCoords(glm::vec3(x - 16, y, z)),
            loader.getChunkAtGlobalCoords(glm::vec3(x + 16, y, z)),
            loader.getChunkAtGlobalCoords(glm::vec3(x, y, z + 16)),
            loader.getChunkAtGlobalCoords(glm::vec3(x, y, z - 16)));
        generateMesh(chunkbounds, loader.loadedChunks[i].meshVertices, loader.loadedChunks[i].meshIndices);
        loader.loadedChunks[i].updateMesh();
        std::cout << i << '\n';
    }
    std::cout << typeid(loader.loadedChunks).name() << '\n';
}
void ChunkMesher::updateMeshForChunkAt(glm::vec3 chunkCoords)
{
    glm::vec3 chunkXYZ = chunkCoords + glm::vec3(loader.RENDER_DISTANCE);
    // Get the index of the desired chunk
    int i = chunkXYZ.x + (chunkXYZ.y * loader.totalWidth) + (chunkXYZ.z * loader.totalWidth * loader.totalWidth);
    // Get the global coordinates of the current chunk
    int x = loader.loadedChunks[i].chunkX * 16.0f;
    int y = loader.loadedChunks[i].chunkY * 16.0f;
    int z = loader.loadedChunks[i].chunkZ * 16.0f;
    // Add in all of the neighboring chunks for face-culling purposes
    ChunkBoundary chunkbounds(loader.loadedChunks[i],
        loader.getChunkAtGlobalCoords(glm::vec3(x, y + 16, z)),
        loader.getChunkAtGlobalCoords(glm::vec3(x, y - 16, z)),
        loader.getChunkAtGlobalCoords(glm::vec3(x - 16, y, z)),
        loader.getChunkAtGlobalCoords(glm::vec3(x + 16, y, z)),
        loader.getChunkAtGlobalCoords(glm::vec3(x, y, z + 16)),
        loader.getChunkAtGlobalCoords(glm::vec3(x, y, z - 16)));
    generateMesh(chunkbounds, loader.loadedChunks[i].meshVertices, loader.loadedChunks[i].meshIndices);
    loader.loadedChunks[i].updateMesh();
}
void ChunkMesher::generateMesh(ChunkBoundary chunk, std::vector<Vertex> &vertexOut, std::vector<GLuint> &indexOut)
{
    int x = 1;
    int y = 1;
    int z = 1;
    for (int i = 0; i < size*size*size; i++)
    {
        if (chunk.get(x,y,z) != AIR)
            buildFaces(chunk, glm::vec3(x,y,z), vertexOut, indexOut);
        x++;
        if (x >= size+1) {
            x = 1;
            y++;
            if (y >= size+1) {
                y = 1;
                z++;
            }
        }
    }
}
void ChunkMesher::buildFaces(ChunkBoundary chunk, glm::vec3 chunkCoords, std::vector<Vertex> &vertexOut, std::vector<GLuint> &indexOut)
{
    glm::vec3 coords = chunk.globalCoords(chunkCoords);
    GLuint block = chunk.get(chunkCoords);
    
    float x = chunkCoords.x;
    float y = chunkCoords.y;
    float z = chunkCoords.z;

    if (!blockTraits[chunk.get(x-1,y,z)].isOpaque)
        addFace(coords, glm::vec3(-1.0f, 0.0f, 0.0f), block, vertexOut, indexOut);
    if (!blockTraits[chunk.get(x+1,y,z)].isOpaque)
        addFace(coords, glm::vec3(1.0f, 0.0f, 0.0f), block, vertexOut, indexOut);
    if (!blockTraits[chunk.get(x,y-1,z)].isOpaque)
        addFace(coords, glm::vec3(0.0f, -1.0f, 0.0f), block, vertexOut, indexOut);
    if (!blockTraits[chunk.get(x,y+1,z)].isOpaque)
        addFace(coords, glm::vec3(0.0f, 1.0f, 0.0f), block, vertexOut, indexOut);
    if (!blockTraits[chunk.get(x,y,z-1)].isOpaque)
        addFace(coords, glm::vec3(0.0f, 0.0f, -1.0f), block, vertexOut, indexOut);
    if (!blockTraits[chunk.get(x,y,z+1)].isOpaque)
        addFace(coords, glm::vec3(0.0f, 0.0f, 1.0f), block, vertexOut, indexOut);
}
void ChunkMesher::addFace(glm::vec3 coords, glm::vec3 normal, GLuint block, std::vector<Vertex> &vertexOut, std::vector<GLuint> &indexOut)
{
    glm::vec3 verts[4];
    glm::vec2 uvs[4] = {{0.0f, 0.0f},
                        {0.0f, 1.0f},
                        {1.0f, 0.0f},
                        {1.0f, 1.0f}};
    if (normal.x != 0.0f) {
        float x = coords.x + 0.5f * normal.x;
        verts[0] = glm::vec3(x, coords.y - 0.5f, coords.z - 0.5f);
        verts[1] = glm::vec3(x, coords.y + 0.5f, coords.z - 0.5f);
        verts[2] = glm::vec3(x, coords.y - 0.5f, coords.z + 0.5f);
        verts[3] = glm::vec3(x, coords.y + 0.5f, coords.z + 0.5f);
    }
    if (normal.y != 0.0f) {
        float y = coords.y + 0.5f * normal.y;
        verts[0] = glm::vec3(coords.x - 0.5f, y, coords.z - 0.5f);
        verts[1] = glm::vec3(coords.x - 0.5f, y, coords.z + 0.5f);
        verts[2] = glm::vec3(coords.x + 0.5f, y, coords.z - 0.5f);
        verts[3] = glm::vec3(coords.x + 0.5f, y, coords.z + 0.5f);
    }
    if (normal.z != 0.0f) {
        float z = coords.z + 0.5f * normal.z;
        verts[0] = glm::vec3(coords.x - 0.5f, coords.y - 0.5f, z);
        verts[1] = glm::vec3(coords.x - 0.5f, coords.y + 0.5f, z);
        verts[2] = glm::vec3(coords.x + 0.5f, coords.y - 0.5f, z);
        verts[3] = glm::vec3(coords.x + 0.5f, coords.y + 0.5f, z);
    }
    GLuint i = vertexOut.size();
    for (int i = 0; i < 4; i++) {
        vertexOut.push_back(Vertex{verts[i], normal, uvs[i], block});
    }
    if (normal.x+normal.y-normal.z>0) { indexOut.insert(indexOut.end(), {i,i+1,i+2,i+2,i+1,i+3}); }
    else { indexOut.insert(indexOut.end(), {i,i+2,i+1,i+1,i+2,i+3}); }
}
int ChunkMesher::chunkIndex(glm::vec3 coords)
{
    return coords.x + (coords.y * size) + (coords.z * size * size);
}
glm::vec3 ChunkMesher::chunkCoords(int index)
{
    glm::vec3 coords;
    coords.x = index % size;
    coords.y = int(glm::floor(index/size)) % size;
    coords.z = glm::floor(index / (size * size));
    return coords;
}
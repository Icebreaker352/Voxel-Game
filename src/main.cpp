#include <iostream>
#include <Mesh.h>
#include <ChunkMesher.h>
#include <compShader.h>
using namespace std;

std::vector<Vertex> planeVert = {
    Vertex{glm::vec3(-1, -1, 0)},
    Vertex{glm::vec3(1, -1, 0)},
    Vertex{glm::vec3(-1, 1, 0)},
    Vertex{glm::vec3(1, 1, 0)}};
std::vector<GLuint>
    planeInd = {0, 1, 2, 1, 2, 3};

string res(string p)
{
    std::filesystem::path path(__FILE__);
    return path.parent_path().string() + "/../res/" + p;
}

int main()
{
    glfwInit();

    // Tell GLFW the version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Use the CORE Profile to only load modern funcitions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Minecraft Knockoff", monitor, NULL);
    // Throw an error if the window does not initialize
    if (window == NULL)
    {
        cout << "Failed to create GLFW Window." << endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Configure OpenGL
    gladLoadGL();
    glViewport(0, 0, mode->width, mode->height);

    // Create all the shaders
    Shader shader(res("shaders/default.vert").c_str(), res("shaders/terrain.frag").c_str());
    Shader planeShader(res("shaders/plane.vert").c_str(), res("shaders/plane.frag").c_str());
    CompShader perlin(res("shaders/perlin.glsl").c_str());

    // OpenGL by default doesn't depth sort by default for some reason
    glEnable(GL_DEPTH_TEST);
    // Enables Gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);

    TextureArray tex({
        res("textures/blocks/cobblestone.png").c_str(),
        res("textures/blocks/diamond_block.png").c_str(),
        res("textures/blocks/diamond_ore.png").c_str(),
        res("textures/blocks/dirt.png").c_str(),
        res("textures/blocks/gold_block.png").c_str(),
        // res("textures/blocks/grass_block_side.png").c_str(),
        res("textures/blocks/grass_block_top.png").c_str(),
        res("textures/blocks/oak_leaves.png").c_str(),
        // res("textures/blocks/oak_log_top.png").c_str(),
        res("textures/blocks/oak_log.png").c_str(),
        res("textures/blocks/oak_planks.png").c_str(),
        res("textures/blocks/stone.png").c_str(),
    }, GL_TEXTURE0);
    GLuint screenTex;
    glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
    glTextureStorage2D(screenTex, 1, GL_RGBA32F, mode->width, mode->height);
    glBindImageTexture(1, screenTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    Mesh plane(planeVert, planeInd);

    // Create the camera 2 units back
    Camera camera(mode->width, mode->height, glm::vec3(0.0f, 0.0f, 8.0f));

    shader.Activate();
    tex.texUnit(shader, "terrainTex");

    // ChunkMesher mesher;

    // Set buffer swap interval to 1. This effectively enables VSync
    glfwSwapInterval(1);

    // Main Loop
    float lastTime = 0.0f;
    float deltaTime = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        deltaTime = float(glfwGetTime()) - lastTime;
        lastTime += deltaTime;

        glClearColor(0.04f, 0.0425f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // for (Chunk chunk : mesher.loader.loadedChunks)
        // {
        //     chunk.chunkMesh.Draw(shader, camera);
        // }

        perlin.Activate();
        glUniform1f(glGetUniformLocation(perlin.ID, "seed"), 1.0f);
        perlin.Dispatch((GLuint)ceil(mode->width / 16.0f), (GLuint)ceil(mode->height / 16.0f), 1);

        plane.Draw(planeShader, screenTex);

        glfwSwapBuffers(window);
        // Take care of GLFW events
        glfwPollEvents();

        camera.Inputs(window, deltaTime);
        camera.updateMatrix(90, 0.1f, 100.0f);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(0);
    return 0;
}
#include <iostream>
#include <Mesh.h>
#include <ChunkMesher.h>
using namespace std;

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

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Minecraft Knockoff", NULL, NULL);
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

    // OpenGL by default doesn't depth sort by default for some reason
    glEnable(GL_DEPTH_TEST);
    // Enables Gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Create the camera 2 units back
    Camera camera(mode->width, mode->height, glm::vec3(0.0f, 0.0f, 8.0f));

    ChunkMesher mesher;
    std::cout << mesher.loader.loadedChunks[0].meshVertices.size() << '\n';

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

        for (Chunk chunk : mesher.loader.loadedChunks)
        {
            chunk.chunkMesh.Draw(shader, camera);
        }

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
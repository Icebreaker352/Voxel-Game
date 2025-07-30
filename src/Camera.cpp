#include <Camera.h>

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    // Initialize Matrices to be the identity matrix
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Looks in the right direction
    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, 0.1f, 100.0f);

    camMatrix = projection * view;
}

void Camera::Matrix(Shader &shader, const char *uniform)
{
    // Input the camera's matrices into the shader program, to apply it to the vertices
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}

void Camera::Inputs(GLFWwindow *window, float delta)
{
    // Take in WASD inputs to move around the camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // Adding the Position and Orientation vectors together will make the cammera move forward
        Position += speed * delta * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // The Cross product of the orientation, and (0, 1, 0) will make the player move horizontally perpendicular to the orientation
        Position += speed * delta * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // Subtracting the Position and Orientation vectors together will make the cammera move forward
        Position += speed * delta * -glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += speed * delta * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += speed * delta * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        Position += speed * delta * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        speed = 4.0f;
    } else {
        speed = 6.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (firstLeftClick) {
            firstLeftClick = false;
            std::cout << "Left Click Registered!\n";
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) firstLeftClick = true;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (firstRightClick) {
            firstRightClick = false;
            // chunks.set(Position, GOLD_BLOCK);
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) firstRightClick = true;

    if (true)
    {
        // Hide the mouse cursor while rotating the camera
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Calibrate the mouse coordinates to match OpenGL coordinates, and multiply by the sensitivity
        float rotX = sensitivity * (float)(mouseY - height / 2) / height;
        float rotY = sensitivity * (float)(mouseX - width / 2) / height;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        // Make sure the player doesn't break their neck by looking back too far
        if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            Orientation = newOrientation;
        }

        // Rotate the camera around the Y-Axis based on horizontal mouse input (Up vector)
        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        glfwSetCursorPos(window, width / 2, height / 2);
    }
}
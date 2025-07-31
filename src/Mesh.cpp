#include <Mesh.h>

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;

    VAO.Bind();

    // Create the Vertex Buffer Object, and the Element Buffer Object
    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    // Add an attribute to store normal vectors
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
    // Add an attribute to store texture coordinates
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
    // Add an attribute to store texture depth
    VAO.LinkIAttrib(VBO, 3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void *)(8 * sizeof(float)));
    // Unbind everything so it doesn't get accidentally changed
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}
Mesh::Mesh()
{
    VAO.Bind();

    // Create the Vertex Buffer Object, and the Element Buffer Object
    VBO VBO(Mesh::vertices);
    EBO EBO(Mesh::indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    // Add an attribute to store normal vectors
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
    // Add an attribute to store texture coordinates
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
    // Add an attribute to store texture depth
    VAO.LinkIAttrib(VBO, 3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void *)(8 * sizeof(float)));
    // Unbind everything so it doesn't get accidentally changed
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera)
{
    shader.Activate();
    VAO.Bind();

    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, 0);
    VAO.Unbind();
}
void Mesh::Draw(Shader &shader, GLuint tex)
{
    shader.Activate();
    glBindTextureUnit(1, tex);
    glUniform1i(glGetUniformLocation(shader.ID, "screen"), 1);
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, 0);
    VAO.Unbind();
}
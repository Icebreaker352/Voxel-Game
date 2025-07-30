#include <VAO.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

// Adds a property that can be accessed by the shader program
void VAO::LinkAttrib(VBO &VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, void *offset)
{
    VBO.Bind();
    // Configure the type of layout so that OpenGL knows how to read the Vertices
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}
void VAO::LinkIAttrib(VBO &VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, void *offset)
{
    VBO.Bind();
    // Configure the type of layout so that OpenGL knows how to read the Vertices
    glVertexAttribIPointer(layout, numComponents, type, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteBuffers(1, &ID);
}
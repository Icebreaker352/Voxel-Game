#ifndef TEXTURE_ARRAY_CLASS_H
#define TEXTURE_ARRAY_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <shaderClass.h>
#include <vector>

class TextureArray
{
public:
    GLuint ID;
    GLuint unit;

    TextureArray(const std::vector<const char*> &images, GLenum slot);

    void texUnit(Shader &shader, const char *uniform);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // TEXTURE_CLASS_H
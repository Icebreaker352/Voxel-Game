#include <TextureArray.h>

TextureArray::TextureArray(const std::vector<const char*>& images, GLenum slot)
{
    GLint widthImg, heightImg, numColCh;
    // stbi and OpenGL have different coordinate systems. Stbi's will be flipepd to match
    stbi_set_flip_vertically_on_load(true);
    // Load in the image, and gather data about it
    unsigned char *first = stbi_load(images[0], &widthImg, &heightImg, &numColCh, 0);

    // Configure the Texture Object
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
    // Set the texture filter to Nearest Neighbor
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Set the texture wrapping to Repeat, so it tiles.
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set the format
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_SRGB_ALPHA, widthImg, heightImg, images.size()+1, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Upload each image to the texture array
    for (size_t i = 0; i < images.size(); ++i) {
        GLint w, h, c;
        unsigned char* data = stbi_load(images[i], &w, &h, &c, 4); // Force 4 channels (RGBA)
        if (data) {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i+1, widthImg, heightImg, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureArray::texUnit(Shader &shader, const char *uniform)
{
    GLuint texUnit = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUnit, unit);
}

void TextureArray::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}

void TextureArray::Unbind()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureArray::Delete()
{
    glDeleteTextures(1, &ID);
}
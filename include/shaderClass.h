#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cerrno>

std::string get_file_contents(const char *filename);

class Shader
{
public:
    GLuint ID;
    int widthImg, heightImg, numColCh;
    Shader(const char *vertFile, const char *fragFile);

    void Activate();
    void Delete();
private:
    void compileErrors(unsigned int shader, const char *type);
};

#endif
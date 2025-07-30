#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cerrno>
#include <vector>

std::string get_file_contents(const char *filename);

class CompShader
{
public:
    GLuint ID;
    int widthImg, heightImg, numColCh;
    CompShader(const char *compFile);

    void Activate();
    void Dispatch(GLuint x, GLuint y, GLuint z);
    void Delete();

private:
    void compileErrors(unsigned int shader, const char *type);
};

#endif
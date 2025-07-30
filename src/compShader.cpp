#include <compShader.h>

CompShader::CompShader(const char *compFile)
{
    // Read the vertex and fragment shader files
    std::string compCode = get_file_contents(compFile);

    // convert the source code to c style strings, because that's what OpenGL uses
    const char *compSource = compCode.c_str();

    // Create the compute shader
    GLuint compShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compShader, 1, &compSource, NULL);
    glCompileShader(compShader);
    compileErrors(compShader, "COMPUTE");

    // Create a shader program
    ID = glCreateProgram();
    // Attach the shaders to the shader program
    glAttachShader(ID, compShader);
    // Wrap the attached shaders together into the shader program
    glLinkProgram(ID);
    // Again, log any errors that are detected
    compileErrors(compShader, "PROGRAM");

    // Delete the shader, as they are no longer needed, and have already been applied to the shader program
    glDeleteShader(compShader);
}

void CompShader::Activate()
{
    glUseProgram(ID);
}

void CompShader::Dispatch(GLuint x, GLuint y, GLuint z)
{
    glDispatchCompute(x, y, z);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void CompShader::Delete()
{
    glDeleteProgram(ID);
}

void CompShader::compileErrors(GLuint shader, const char *type)
{
    GLint hasCompiled;
    char infoLog[1024];
    if (type != "Program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for " << type << ": " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "PROGRAM_LINKING_ERROR for " << type << ": " << infoLog << std::endl;
        }
    }
}
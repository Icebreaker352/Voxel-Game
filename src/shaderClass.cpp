#include <shaderClass.h>

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw(errno);
}

Shader::Shader(const char *vertFile, const char *fragFile)
{
    // Read the vertex and fragment shader files
    std::string vertCode = get_file_contents(vertFile);
    std::string fragCode = get_file_contents(fragFile);

    // convert the source code to c style strings, because that's what OpenGL uses
    const char *vertSource = vertCode.c_str();
    const char *fragSource = fragCode.c_str();

    // Create vertex shader
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    // Apply the vertex shader source code to the shader
    glShaderSource(vertShader, 1, &vertSource, NULL);
    // Turn the shader into machine code
    glCompileShader(vertShader);
    // If any errors are detected, they will be logged to the console
    compileErrors(vertShader, "VERTEX");

    // Same as above but for the fragment shader instead
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    compileErrors(fragShader, "FRAGMENT");

    // Create a shader program
    ID = glCreateProgram();
    // Attach the shaders to the shader program
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    // Wrap the attached shaders together into the shader program
    glLinkProgram(ID);
    // Again, log any errors that are detected
    compileErrors(vertShader, "PROGRAM");

    // Delete the two shaders, as they are no longer needed, and have already been applied to the shader program
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::compileErrors(GLuint shader, const char *type)
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
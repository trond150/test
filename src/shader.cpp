#include "shader.h"
#include "glfw_common.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
    std::string vertex_shader = read_file(vertex_path);
    std::string fragment_shader = read_file(fragment_path);

    int success;
    char infoLog[512];
   
    // vertex Shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_code = vertex_shader.c_str();
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // fragment Shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_code = fragment_shader.c_str();
    glShaderSource(fragment, 1, &fragment_code, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // create program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
  
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::set_bool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}

void Shader::set_int(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}

void Shader::set_float(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
}

std::string Shader::read_file(const std::string& path) const
{
    std::string shader = "";
    std::ifstream file;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        file.open(path);
        std::stringstream shader_stream;
        shader_stream << file.rdbuf();	
        file.close();
        shader = shader_stream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return shader;
}
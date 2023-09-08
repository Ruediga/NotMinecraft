#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
    // shader ID
    unsigned int ID;

    // shader constructor
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        std::string vs_code, fs_code;
        std::ifstream vs_file, fs_file;

        vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vs_file.open(vertexShaderPath);
            fs_file.open(fragmentShaderPath);

            std::stringstream vsc_buffer, fsc_buffer;

            vsc_buffer << vs_file.rdbuf();
            fsc_buffer << fs_file.rdbuf();

            vs_file.close();
            fs_file.close();

            vs_code = vsc_buffer.str();
            fs_code = fsc_buffer.str();
        }
        catch (std::ifstream::failure& failure)
        {
            std::cerr << "ERROR -> Shader -> file reading exception: " << failure.what() << std::endl;
        }

        // std::string.c_str() is inexpensive! doesn't copy, but return a pointer to array
        const char* vertex_shader_code{ vs_code.c_str() };
        const char* fragment_shader_code{ fs_code.c_str() };

        // Shader compilation
        unsigned int vertexShader, fragmentShader;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_shader_code, NULL);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_shader_code, NULL);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // usage and uniform functions (extend list when needed)
    void use()
    {
        glUseProgram(ID);
    }
    void setInt(const std::string& name, const int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, const float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void setMat4(const std::string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

private:
    // util
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                GLchar infoLog[1024];
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR -> Shader -> shader compilation failed: " << type << "\n" << infoLog << std::endl;
            }
        }

        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                GLchar infoLog[1024];
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR -> Shader Program -> linking error: " << type << "\n" << infoLog << std::endl;
            }
        }
    }
};
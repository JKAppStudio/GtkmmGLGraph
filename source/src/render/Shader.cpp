/**
 * @file Shaders.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief OpenGL shader management implementation
 * @version 0.1
 * @date 2025-09-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Shader.hpp"
#include <iostream>

namespace Gtkmm {
namespace GLGraph {

void Shader::init(const std::string& vertexSource, const std::string& geometrySource, const std::string& fragmentSource) {
    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vSrc = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vSrc, nullptr);
    glCompileShader(vertexShader);
    check_shader_compile(vertexShader, "VERTEX");

    GLint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    const char* gSrc = geometrySource.c_str();
    glShaderSource(geometryShader, 1, &gSrc, nullptr);
    glCompileShader(geometryShader);
    check_shader_compile(geometryShader, "GEOMETRY");

    GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fSrc = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fSrc, nullptr);
    glCompileShader(fragmentShader);
    check_shader_compile(fragmentShader, "FRAGMENT");

    // Link program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    check_program_link(program);
}

void Shader::check_shader_compile(GLuint shader, const std::string &type)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << type << " SHADER COMPILATION FAILED:\n" << log << std::endl;
    }
}

void Shader::check_program_link(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "SHADER PROGRAM LINKING FAILED:\n" << log << std::endl;
    }
}

} // namespace GLGraph
} // namespace Gtkmm

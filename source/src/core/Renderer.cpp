/**
 * @file Renderer.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief OpenGL helper functions implementation
 * @version 0.1
 * @date 2025-09-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Renderer.hpp"
#include <iostream>

namespace Gtkmm {
namespace GLGraph {

float vertices[] = {
    // pos        // color
    -0.6f, -0.4f, 1.0f, 0.0f, 0.0f,
    0.6f, -0.4f, 1.0f, 0.0f, 0.0f,
    0.0f,  0.6f, 1.0f, 0.0f, 0.0f
};

// Simple vertex and fragment shaders for axis rendering
static const std::string vertexShaderSrc = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    out vec3 vColor;
    void main() {
        gl_Position = vec4(aPos, 1.0);
        vColor = aColor;
    }
)";

static const std::string fragmentShaderSrc = R"(
    #version 330 core
    in vec3 vColor;
    out vec4 FragColor;
    void main() {
        FragColor = vec4(vColor, 1.0);
    }
)";

Renderer::Renderer(void)
{}

Renderer::~Renderer(void)
{
    cleanup();
}

void Renderer::init(void)
{
    _axisShader.init(vertexShaderSrc, fragmentShaderSrc);
}

void Renderer::cleanup(void)
{
    glDeleteProgram(_axisShader.program);
}

} // namespace GLGraph
} // namespace Gtkmm
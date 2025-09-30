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

Renderer::~Renderer(void)
{
    cleanup_internal();
}

void Renderer::init_internal(const std::string& vertexSource, const std::string& geometrySource, const std::string& fragmentSource)
{
    _shader.init(vertexSource, geometrySource, fragmentSource);
    glGenVertexArrays(1, &_vert_array);
    glGenBuffers(1, &_vert_buffer);
}

void Renderer::cleanup_internal(void)
{
    if (_shader.program != 0)
        glDeleteProgram(_shader.program);
    _shader.program = 0;

    if (_vert_array != 0)
        glDeleteVertexArrays(1, &_vert_array);
    _vert_array = 0;

    if (_vert_buffer != 0)
        glDeleteBuffers(1, &_vert_buffer);
    _vert_buffer = 0;
}

Viewport Renderer::get_viewport(void)
{
    Viewport vp;
    glGetIntegerv(GL_VIEWPORT, (GLint*)&vp);
    return vp;
}

} // namespace GLGraph
} // namespace Gtkmm
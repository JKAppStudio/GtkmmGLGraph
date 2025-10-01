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

bool Renderer::draw_points(const std::vector<Vertex> &points)
{
    if (points.empty())
        return true;

    glBindVertexArray(_vert_array);
    glBindBuffer(GL_ARRAY_BUFFER, _vert_buffer);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Vertex), points.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(_vert_array);
    glDrawArrays(GL_POINTS, 0, points.size());

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

void Renderer::init_internal(const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource)
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

Viewport Renderer::get_context_viewport(void)
{
    Viewport vp;
    glGetIntegerv(GL_VIEWPORT, (GLint*)&vp);
    return vp;
}

} // namespace GLGraph
} // namespace Gtkmm
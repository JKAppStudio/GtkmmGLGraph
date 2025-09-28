/**
 * @file Renderer.hpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief OpenGL helper 
 * @version 0.1
 * @date 2025-09-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __GTKMM_GLRENDERER_HPP__
#define __GTKMM_GLRENDERER_HPP__

#include "Axis.hpp"
#include "Shader.hpp"

#include <epoxy/gl.h>
#include <string>

namespace Gtkmm{
namespace GLGraph{

class Renderer{
public:
    Renderer(void);
    virtual ~Renderer(void);

    template<typename T>
    bool draw_axes(const std::vector<Axis<T>>& axes);
    void init(void);
    void cleanup(void);
private:
    Shader _axisShader;
    GLuint _axes_va = 0, _axes_vb = 0;
};

extern float vertices[15];

template <typename T>
inline bool Renderer::draw_axes(const std::vector<Axis<T>>& axes)
{

    // Generate VAO & VBO
    glGenVertexArrays(1, &_axes_va);
    glGenBuffers(1, &_axes_vb);

    glBindVertexArray(_axes_va);
    glBindBuffer(GL_ARRAY_BUFFER, _axes_vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(_axisShader.program);
    glBindVertexArray(_axes_va);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_LINE_LOOP, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);
    return true;
}

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_GLRENDERER_HPP__


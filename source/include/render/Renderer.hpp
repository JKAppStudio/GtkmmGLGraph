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

#include "Shader.hpp"

#include <epoxy/gl.h>
#include <string>
#include <vector>

namespace Gtkmm{
namespace GLGraph{

#pragma pack(push, 1)
struct Vertex {
    float x,y;
};

struct Viewport {
    int x, y;
    int width, height;
};

template<typename T>
struct Rect{
    T x, y, width, height;
};

template<typename T>
struct Vec2{
    T x, y;
};

template<typename T>
struct Vec3{
    T x, y, z;
};
#pragma pack(pop)

class Renderer{
public:
    Renderer(void) = default;
    virtual ~Renderer(void);

    virtual void init(void) = 0;
    virtual void cleanup(void) = 0;
    static Viewport get_context_viewport(void); 

    void set_ndc(const Vec2<float>& ndc) { _ndc = ndc; }
    void set_ndc_draw_rect(const Rect<float>& rect) { _ndc_draw_rect = rect; }
    void set_draw_rect(const Rect<int>& draw_rect) { _draw_rect = draw_rect; }

protected:
    void init_internal(const std::string& vertexSource, const std::string& geometrySource, const std::string& fragmentSource);
    void cleanup_internal(void);
    
    bool draw_points(const std::vector<Vertex>& points);

protected:
    Shader _shader;
    GLuint _vert_array = 0;
    GLuint _vert_buffer = 0;

    Vec2<float> _ndc{1.0f, 1.0f};
    Rect<float> _ndc_draw_rect{-1.0f, -1.0f, 1.0f, 1.0f};
    Rect<int> _draw_rect{0, 0, 800, 600};
};

// extern float vertices[15];

// inline bool Renderer::draw_axes(const std::vector<Axis>& axes)
// {
//     glBindVertexArray(_axes_va);
//     glBindBuffer(GL_ARRAY_BUFFER, _axes_vb);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // Position attribute
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Color attribute
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

//     glUseProgram(_axisShader.program);
//     glBindVertexArray(_axes_va);
//     glDrawArrays(GL_POINTS, 0, 3);

//     glBindVertexArray(0);
//     glUseProgram(0);
//     return true;
// }

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_GLRENDERER_HPP__


/**
 * @file XYAxisRenderer.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief Cartesian Axis Renderer for X and Y axes implementation
 * @version 0.1
 * @date 2025-09-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "XYAxisRenderer.hpp"

// Simple vertex and fragment shaders for axis rendering
static const std::string axisVertexShaderSrc = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform vec4 aColor;
    out vec4 vColor;
    void main() {
        gl_Position = vec4(aPos, 1.0);
        vColor = aColor;
    }
)";

static const std::string axisGeometryShaderSrc = R"(
    #version 330 core
    layout(points) in;
    layout(triangle_strip, max_vertices = 4) out;
    uniform int axis; // 0 for X, 1 for Y
    uniform float half_width;
    uniform float length;

    in vec4 vColor[];       
    out vec4 gColor; 

    void main() {
        // Emit 4 vertices of a line with given width and length
        gl_Position = gl_in[0].gl_Position + (axis == 0 ? vec4(-half_width, 0.0, 0.0, 0.0) : vec4(0.0, -half_width, 0.0, 0.0));
        gColor = vColor[0];
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + (axis == 0 ? vec4(half_width, 0.0, 0.0, 0.0) : vec4(0.0, half_width, 0.0, 0.0));
        gColor = vColor[0];
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + (axis == 0 ? vec4(-half_width, length, 0.0, 0.0) : vec4(length, -half_width, 0.0, 0.0));
        gColor = vColor[0];
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + (axis == 0 ? vec4(half_width, length, 0.0, 0.0) : vec4(length, half_width, 0.0, 0.0));
        gColor = vColor[0];
        EmitVertex();

        EndPrimitive();
    }
)";

static const std::string axisFragmentShaderSrc = R"(
    #version 330 core
    in vec4 gColor;
    out vec4 FragColor;
    void main() {
        FragColor = gColor;
    }
)";

using namespace Gtkmm::GLGraph;

void XYAxisRenderer::init(void)
{
    init_internal(axisVertexShaderSrc, axisGeometryShaderSrc, axisFragmentShaderSrc);
}

void XYAxisRenderer::cleanup(void)
{
    cleanup_internal();
}

bool XYAxisRenderer::draw_axes(std::vector<Axis>& axes)
{
    const Viewport vp = get_viewport();
    const float pixel_to_ndc_x = 2.0f / vp.width;
    const float pixel_to_ndc_y = 2.0f / vp.height;

    const int margin_pix = 40;

    Rect<float> plot_area = {
        -1.0f + margin_pix * pixel_to_ndc_x, 
        -1.0f + margin_pix * pixel_to_ndc_y,
        (float)(vp.width - margin_pix) * pixel_to_ndc_x, 
        (float)(vp.height - margin_pix) * pixel_to_ndc_y
    };

    // Bind shaders and buffers
    glBindVertexArray(_vert_array);
    glBindBuffer(GL_ARRAY_BUFFER, _vert_buffer);
    glUseProgram(_shader.program);

    for (const auto& axis : axes) {
        glUniform4f(glGetUniformLocation(_shader.program, "aColor"), 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform1i(glGetUniformLocation(_shader.program, "axis"), axis.type() == AXIS_X ? 0 : 1);
        glUniform1f(glGetUniformLocation(_shader.program, "half_width"), (2.0f / 2.0f) * (axis.type() == AXIS_X ? pixel_to_ndc_x : pixel_to_ndc_y));
        glUniform1f(glGetUniformLocation(_shader.program, "length"), (axis.type() == AXIS_X ? plot_area.height : plot_area.width));

        std::vector<Vertex> vertices;
        const float main_step = (axis.max() - axis.min()) / 10.0f;
        const float sub_step = main_step / 5.0f;
        if(axis.type() == AXIS_X) {
            vertices = {
                {plot_area.x, plot_area.y},
                {plot_area.x + plot_area.width / 2.0f, plot_area.y},
                {plot_area.x + plot_area.width, plot_area.y}
            };
        } else if(axis.type() == AXIS_Y) {
            vertices = {
                {plot_area.x, plot_area.y},
                {plot_area.x, plot_area.y + plot_area.height / 2.0f},
                {plot_area.x, plot_area.y + plot_area.height}
            };
        }

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_POINTS, 0, vertices.size());
        // Set the color based on the axis
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    return true;
}

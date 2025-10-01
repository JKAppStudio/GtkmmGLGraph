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
#include <cmath>

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
    uniform int style; // 0 solid, 1 dashed, 2 dotted
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

bool XYAxisRenderer::draw_axes(const Axis& _x_axis, const Axis& _y_axis)
{
    std::vector<Vertex> vertices;

    // Bind shaders and buffers
    glBindVertexArray(_vert_array);
    glBindBuffer(GL_ARRAY_BUFFER, _vert_buffer);
    glUseProgram(_shader.program);

    /* Draw Plot area border */
    // Vertical lines
    glUniform4f(
        glGetUniformLocation(_shader.program, "aColor"), 
        _x_axis.color().get_red(), 
        _x_axis.color().get_green(), 
        _x_axis.color().get_blue(), 
        _x_axis.color().get_alpha()
    );
    glUniform1i(glGetUniformLocation(_shader.program, "axis"), 0);
    glUniform1i(glGetUniformLocation(_shader.program, "style"), 0);
    glUniform1f(glGetUniformLocation(_shader.program, "half_width"), (1.0f / 2.0f) * _ndc.x);
    glUniform1f(glGetUniformLocation(_shader.program, "length"), _ndc_draw_rect.height);
    vertices.push_back({_ndc_draw_rect.x, _ndc_draw_rect.y});
    vertices.push_back({_ndc_draw_rect.x + _ndc_draw_rect.width, _ndc_draw_rect.y});

    draw_points(vertices);
    vertices.clear();

    // Horizontal lines
    glUniform4f(
        glGetUniformLocation(_shader.program, "aColor"), 
        _y_axis.color().get_red(), 
        _y_axis.color().get_green(), 
        _y_axis.color().get_blue(), 
        _y_axis.color().get_alpha()
    );
    glUniform1i(glGetUniformLocation(_shader.program, "axis"), 1);
    glUniform1i(glGetUniformLocation(_shader.program, "style"), 0);
    glUniform1f(glGetUniformLocation(_shader.program, "half_width"), (1.0f / 2.0f) * _ndc.y);
    glUniform1f(glGetUniformLocation(_shader.program, "length"), _ndc_draw_rect.width);
    vertices.push_back({_ndc_draw_rect.x, _ndc_draw_rect.y});
    vertices.push_back({_ndc_draw_rect.x, _ndc_draw_rect.y + _ndc_draw_rect.height});

    draw_points(vertices);
    vertices.clear();
    const auto grid_params_x = calculate_grid_parameters(_x_axis);
    const auto grid_params_y = calculate_grid_parameters(_y_axis);

    /* Draw grid lines */
    // X axis major grid lines
    glUniform1i(glGetUniformLocation(_shader.program, "axis"), 0);
    glUniform1i(glGetUniformLocation(_shader.program, "style"), _x_axis.major_grid_style());
    glUniform1f(glGetUniformLocation(_shader.program, "half_width"), grid_params_x[0].ndc_width / 2.0f);
    glUniform1f(glGetUniformLocation(_shader.program, "length"), _ndc_draw_rect.height);
    for(size_t i = 1; i < grid_params_x[0].ticks - 1; i++) {
        vertices.push_back(
            {_ndc_draw_rect.x + (i * grid_params_x[0].ndc_step), _ndc_draw_rect.y}
        );
    }
    draw_points(vertices);
    vertices.clear();

    // Y axis major grid lines
    glUniform1i(glGetUniformLocation(_shader.program, "axis"), 1);
    glUniform1i(glGetUniformLocation(_shader.program, "style"), _y_axis.major_grid_style());
    glUniform1f(glGetUniformLocation(_shader.program, "half_width"), grid_params_y[0].ndc_width / 2.0f);
    glUniform1f(glGetUniformLocation(_shader.program, "length"), _ndc_draw_rect.width);
    for(size_t i = 1; i < grid_params_y[0].ticks - 1; i++) {
        vertices.push_back(
            {_ndc_draw_rect.x, _ndc_draw_rect.y + (i * grid_params_y[0].ndc_step)}
        );
    }
    draw_points(vertices);
    vertices.clear();
    // for (const auto& axis : axes) {
    //     glUniform4f(glGetUniformLocation(_shader.program, "aColor"), 1.0f, 1.0f, 1.0f, 1.0f);
    //     glUniform1i(glGetUniformLocation(_shader.program, "axis"), axis.type() == AXIS_X ? 0 : 1);
    //     glUniform1f(glGetUniformLocation(_shader.program, "half_width"), (2.0f / 2.0f) * (axis.type() == AXIS_X ? pixel_to_ndc_x : pixel_to_ndc_y));
    //     glUniform1f(glGetUniformLocation(_shader.program, "length"), (axis.type() == AXIS_X ? plot_area.height : plot_area.width));

    //     const float main_step = (axis.max() - axis.min()) / 10.0f;
    //     const float sub_step = main_step / 5.0f;
    //     if(axis.type() == AXIS_X) {
    //         vertices = {
    //             {plot_area.x, plot_area.y},
    //             {plot_area.x + plot_area.width / 2.0f, plot_area.y},
    //             {plot_area.x + plot_area.width, plot_area.y}
    //         };
    //     } else if(axis.type() == AXIS_Y) {
    //         vertices = {
    //             {plot_area.x, plot_area.y},
    //             {plot_area.x, plot_area.y + plot_area.height / 2.0f},
    //             {plot_area.x, plot_area.y + plot_area.height}
    //         };
    //     }

    //     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    //     // Position attribute
    //     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //     glEnableVertexAttribArray(0);

    //     glDrawArrays(GL_POINTS, 0, vertices.size());
    //     // Set the color based on the axis
    // }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    return true;
}

std::vector<XYAxisRenderer::GridParameters> 
XYAxisRenderer::calculate_grid_parameters(const Axis &axis, size_t desired_ticks)
{
    std::vector<GridParameters> grid_params(2); // Major and minor grid parameters
    const int length = axis.type() == AXIS_X ? _draw_rect.width : _draw_rect.height;

    const float major_ndc_width = 
        axis.type() == AXIS_X ? axis.major_grid_line_width() * _ndc.x : axis.major_grid_line_width() * _ndc.y;
    float major_start, major_step, major_ndc_step;

    /* Calculate major ticks */
    size_t major_ticks = desired_ticks > 2 ? desired_ticks : 2;
    int pixel_delta = length / major_ticks;
    while (
        pixel_delta < ((axis.major_grid_line_width() / 2) + Axis::MIN_MAJOR_GRID_DISTANCE_PX) 
        && major_ticks > 2
    ) {
        major_ticks--;
        pixel_delta = length / major_ticks;
    }
    while (
        pixel_delta > (axis.major_grid_line_width() / 2) + Axis::MAX_MAJOR_GRID_DISTANCE_PX
    ) {
        major_ticks++;
        pixel_delta = length / major_ticks;
    }

    /* Calculate steps and starts */
    if(major_ticks > 2){
        
        float delta = std::abs(axis.max() - axis.min()) / (major_ticks - 1); // N ticks create N-1 intervals
        const float delta_digit = (int)(std::log10(delta) / 1.0f);
        major_step = int(delta / std::pow(10.0f, delta_digit) + 0.5f) * std::pow(10.0f, delta_digit);
        const float center = (axis.max() + axis.min()) / 2.0f;
        major_start = center - (major_step * ((major_ticks - 1) / 2.0f));
    } else {
        major_ticks = 2;
        major_start = axis.min();
        major_step = (axis.max() - axis.min()) / (major_ticks - 1);
    }

    major_ndc_step = axis.type() == AXIS_X ? _ndc_draw_rect.width / (major_ticks - 1) : _ndc_draw_rect.height / (major_ticks - 1);

    grid_params[0].ticks = major_ticks;
    grid_params[0].value_start = major_start;
    grid_params[0].value_step = major_step;
    grid_params[0].ndc_step = major_ndc_step;
    grid_params[0].ndc_width = major_ndc_width;

    /* Calculate minor ticks */
    size_t minor_ticks_per_major = 5; // 4 minor ticks between major ticks
    
    return grid_params;
}

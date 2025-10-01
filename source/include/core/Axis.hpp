/**
 * @file Axis.hpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief Axis representation for graphs
 * @version 0.1
 * @date 2025-09-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __GTKMM_GLGRAPH_AXIS_HPP__
#define __GTKMM_GLGRAPH_AXIS_HPP__

#include <gdkmm/rgba.h>
#include <string>

namespace Gtkmm {
namespace GLGraph {

typedef enum {
    AXIS_X,
    AXIS_Y,
    AXIS_Z
} AxisType;

typedef enum {
    GRID_NONE,
    GRID_MAJOR,
    GRID_MINOR,
    GRID_BOTH
} GridLines;

typedef enum {
    GRID_STYLE_SOLID,
    GRID_STYLE_DASHED,
    GRID_STYLE_DOTTED
} GridStyle;

class Axis 
{
public:
    Axis(AxisType type, const std::string& label, const Gdk::RGBA& color = Gdk::RGBA("Gray"));
    virtual ~Axis(void) {}

    AxisType type(void) const { return _type; }
    float min(void) const { return _min; }
    float max(void) const { return _max; }
    float major_grid_line_width(void) const { return _major_grid_line_width; }
    float minor_grid_line_width(void) const { return _minor_grid_line_width; }
    Gdk::RGBA color(void) const { return _color; }
    GridLines grid(void) const { return _grid; }
    GridStyle major_grid_style(void) const { return _major_grid_style; }
    GridStyle minor_grid_style(void) const { return _minor_grid_style; }
    std::string label(void) const { return _label; }

    void set_min(float value) { _min = value; }
    void set_max(float value) { _max = value; }
    void set_major_grid_line_width(float width) { _major_grid_line_width = width; }
    void set_minor_grid_line_width(float width) { _minor_grid_line_width = width; }
    void set_color(const Gdk::RGBA& color) { _color = color; }
    void set_grid(GridLines grid) { _grid = grid; }
    void set_major_grid_style(GridStyle style) { _major_grid_style = style; }
    void set_minor_grid_style(GridStyle style) { _minor_grid_style = style; }
    void set_label(const std::string& text) { _label = text; }

    static const int MIN_MAJOR_GRID_DISTANCE_PX {60};
    static const int MAX_MAJOR_GRID_DISTANCE_PX {160};
private:
    AxisType _type;
    std::string _label;
    GridLines _grid = GRID_BOTH;
    GridStyle _major_grid_style = GRID_STYLE_SOLID;
    GridStyle _minor_grid_style = GRID_STYLE_DASHED;
    Gdk::RGBA _color;
    float _min = -10.f, _max = 10.f;
    float _major_grid_line_width = 2.f;
    float _minor_grid_line_width = 1.f;
};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_GLGRAPH_AXIS_HPP__
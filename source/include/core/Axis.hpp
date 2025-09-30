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

#include <epoxy/gl.h>
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

class Axis 
{
public:
    Axis(AxisType type, const std::string& label, float min = 0, float max = 10)
        : _type(type), _label(label), _min(min), _max(max) {}
    ~Axis(void) {}

    AxisType type(void) const { return _type; }
    float min(void) const { return _min; }
    float max(void) const { return _max; }
    std::string label(void) const { return _label; }

    void set_min(float value) { _min = value; }
    void set_max(float value) { _max = value; }
    void set_label(const std::string& text) { _label = text; }

private:
    AxisType _type;
    std::string _label;
    GridLines _grid = GRID_BOTH;
    float _min;
    float _max;
};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_GLGRAPH_AXIS_HPP__
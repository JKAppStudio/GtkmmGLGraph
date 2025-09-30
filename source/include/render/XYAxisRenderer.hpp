/**
 * @file XYAxisRenderer.hpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief Cartesian Axis Renderer for X and Y axes
 * @version 0.1
 * @date 2025-09-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __GTKMM_XY_AXIS_RENDERER_HPP__
#define __GTKMM_XY_AXIS_RENDERER_HPP__

#include "Renderer.hpp"
#include "Axis.hpp"

#include <vector>

namespace Gtkmm {
namespace GLGraph {

class XYAxisRenderer : public Renderer {
public:
    XYAxisRenderer(void) = default;
    virtual ~XYAxisRenderer(void) {};

    void init(void) override;
    void cleanup(void) override;
    bool draw_axes(std::vector<Axis>& axes);

};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_XY_AXIS_RENDERER_HPP__
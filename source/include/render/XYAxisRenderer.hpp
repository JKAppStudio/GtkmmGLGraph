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

namespace Gtkmm {
namespace GLGraph {

class XYAxisRenderer : public Renderer {
public:
    XYAxisRenderer(void) = default;
    virtual ~XYAxisRenderer(void) {};

    void init(void) override;
    void cleanup(void) override;
    bool draw_axes(const Axis& _x_axis, const Axis& _y_axis);

protected:
    struct GridParameters {
        float value_start;
        float value_step;
        size_t ticks;
        
        float ndc_step;
        float ndc_width;
    };

    std::vector<GridParameters> calculate_grid_parameters(const Axis& axis, size_t desired_ticks = 5);
};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_XY_AXIS_RENDERER_HPP__
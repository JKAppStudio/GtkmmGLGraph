/**
 * @file GLPlotArea.hpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief GTKMM Gl plot area class
 * @version 0.1
 * @date 2025-09-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __GTKMM_PLOT_AREA_HPP__
#define __GTKMM_PLOT_AREA_HPP__

#include "Axis.hpp"
#include "XYAxisRenderer.hpp"

#include <gtkmm/glarea.h>
#include <vector>

namespace Gtkmm {
namespace GLGraph {

class PlotArea : public Gtk::GLArea 
{
public:
    PlotArea(void);
    virtual ~PlotArea();

    Gdk::RGBA bg_color(void) const { return _bg_color; }
    void set_bg_color(const Gdk::RGBA& color) { _bg_color = color; queue_draw(); }

protected:
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;
    void on_realize(void) override;
    void on_unrealize(void) override;

protected:
    static const int X_AXIS_PADDING_LEFT    {40};
    static const int X_AXIS_PADDING_RIGHT   {10};
    static const int Y_AXIS_PADDING_TOP     {30};
    static const int Y_AXIS_PADDING_BOTTOM  {40};

private:
    Axis _axis_x;
    Axis _axis_y; 

    Gdk::RGBA _bg_color = Gdk::RGBA("White");

    XYAxisRenderer _axes_renderer;
};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_PLOT_AREA_HPP__
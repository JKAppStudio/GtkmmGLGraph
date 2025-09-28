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
#include "Renderer.hpp"

#include <gtkmm/glarea.h>
#include <vector>

namespace Gtkmm {
namespace GLGraph {

class PlotArea : public Gtk::GLArea 
{
public:
    PlotArea(void);
    virtual ~PlotArea();

protected:
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;
    void on_realize(void) override;
    void on_unrealize(void) override;

private:
    std::vector<Axis<float>> _axes;

    Renderer _renderer;
};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_PLOT_AREA_HPP__
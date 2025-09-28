/**
 * @file GLGraph.hpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief GLGraph interface
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __GTKMM_GLGRAPH_HPP__
#define __GTKMM_GLGRAPH_HPP__

#include "PlotArea.hpp"

#include <gtkmm/grid.h>
#include <epoxy/gl.h>

namespace Gtkmm {
namespace GLGraph {

class GLGraph : public Gtk::Grid {
public:
    GLGraph(void);
    virtual ~GLGraph();

protected:

private:
    PlotArea _plotArea;
};

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_GLGRAPH_HPP__
/**
 * @file PlotArea.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "PlotArea.hpp"
#include "Renderer.hpp"

#include <iostream>

using namespace Gtkmm::GLGraph;

PlotArea::PlotArea(void) 
{
    set_required_version(3, 3);
    set_has_depth_buffer(true);

    signal_realize().connect(sigc::mem_fun(*this, &PlotArea::on_realize));
    signal_unrealize().connect(sigc::mem_fun(*this, &PlotArea::on_unrealize));
    signal_render().connect(sigc::mem_fun(*this, &PlotArea::on_render), false);

    _axes.emplace_back(AXIS_X, "X Axis", -10.0f, 10.0f);
    _axes.emplace_back(AXIS_Y, "Y Axis", -10.0f, 10.0f);
}

PlotArea::~PlotArea(void)
{}

bool Gtkmm::GLGraph::PlotArea::on_render(const Glib::RefPtr<Gdk::GLContext> &context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _axes_renderer.draw_axes(_axes);

    return true;
}

void PlotArea::on_realize(void)
{
    Gtk::GLArea::on_realize();
    make_current();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    _axes_renderer.init();
    // Check for context errors
    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "OpenGL context creation failed." << std::endl;
        return;
    }
}

void Gtkmm::GLGraph::PlotArea::on_unrealize(void)
{
    // Must call base implementation last
    Gtk::GLArea::on_unrealize();
    
    _axes_renderer.cleanup();
}

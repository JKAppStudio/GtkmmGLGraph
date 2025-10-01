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
    : _axis_x(AXIS_X, "X Axis")
    , _axis_y(AXIS_Y, "Y Axis")
{
    auto style = get_style_context();
    Gdk::RGBA color;
    if(style->lookup_color("theme_unfocused_fg_color", color)) {
        _axis_x.set_color(color);
        _axis_y.set_color(color);
    }
    style->lookup_color("theme_bg_color", _bg_color);

    set_required_version(3, 3);
    set_has_depth_buffer(true);

    signal_realize().connect(sigc::mem_fun(*this, &PlotArea::on_realize));
    signal_unrealize().connect(sigc::mem_fun(*this, &PlotArea::on_unrealize));
    signal_render().connect(sigc::mem_fun(*this, &PlotArea::on_render), false);
}

PlotArea::~PlotArea(void)
{}

bool Gtkmm::GLGraph::PlotArea::on_render(const Glib::RefPtr<Gdk::GLContext> &context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Figure out geometry */
    const Viewport vp = Renderer::get_context_viewport();

    const Vec2<float> ndc{2.0f / vp.width, 2.0f / vp.height};
    const Rect<int> draw_rect {
        X_AXIS_PADDING_LEFT,
        Y_AXIS_PADDING_BOTTOM,
        vp.width - (X_AXIS_PADDING_LEFT + X_AXIS_PADDING_RIGHT),
        vp.height - (Y_AXIS_PADDING_BOTTOM + Y_AXIS_PADDING_TOP)
    };
    const Rect<float> ndc_draw_rect {
        -1.0f + (X_AXIS_PADDING_LEFT) * ndc.x,
        -1.0f + (Y_AXIS_PADDING_BOTTOM) * ndc.y,
        2.0f - (X_AXIS_PADDING_LEFT + X_AXIS_PADDING_RIGHT) * ndc.x,
        2.0f - (Y_AXIS_PADDING_BOTTOM + Y_AXIS_PADDING_TOP) * ndc.y
    };

    _axes_renderer.set_draw_rect(draw_rect);
    _axes_renderer.set_ndc(ndc);
    _axes_renderer.set_ndc_draw_rect(ndc_draw_rect);

    _axes_renderer.draw_axes(_axis_x, _axis_y);

    return true;
}

void PlotArea::on_realize(void)
{
    Gtk::GLArea::on_realize();
    make_current();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(_bg_color.get_red(), _bg_color.get_green(), _bg_color.get_blue(), _bg_color.get_alpha());
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

/**
 * @file sine_wave.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief Sine wave example using GtkmmGLGraph
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "GLGraph.hpp"

#include <gtkmm.h>
#include <math.h>
#include <vector>

#define APP_ID "org.JKAppStudio.glgraph.sinewave"

class SineWaveWindow : public Gtk::Window {
public:
    SineWaveWindow(void) {
        set_title("Sine Wave Example");
        set_default_size(800, 600);

        _grid.set_margin(10);
        set_child(_grid);
        _grid.attach(_graph, 0, 0);
        _graph.set_expand();
    }
    virtual ~SineWaveWindow(void) {}
private:
    Gtk::Grid _grid;
    Gtkmm::GLGraph::GLGraph _graph;
};

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(APP_ID);

    // Get the default GtkSettings object
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();

    // Set the gtk-application-prefer-dark-theme property to true
    if (settings)
    {
        settings->property_gtk_application_prefer_dark_theme() = true;
    }

    return app->make_window_and_run<SineWaveWindow>(argc, argv);
}
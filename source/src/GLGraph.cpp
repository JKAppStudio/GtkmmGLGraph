/**
 * @file GLGraph.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "GLGraph.hpp"
#include <iostream>

using namespace Gtkmm::GLGraph;

GLGraph::GLGraph() {
    _title.set_text("Graph Title");
    attach(_title, 0, 0, 1, 1);
    attach(_plotArea, 0, 1, 1, 1);
    _plotArea.set_expand();
}

GLGraph::~GLGraph() {
    // Destructor implementation
}
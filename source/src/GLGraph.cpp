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
    attach(_plotArea, 0, 1, 1, 1);
    _plotArea.set_expand();
    _plotArea.set_size_request(MIN_PLOT_AREA_SIZE_X, MIN_PLOT_AREA_SIZE_Y);
}

GLGraph::~GLGraph() {
    // Destructor implementation
}
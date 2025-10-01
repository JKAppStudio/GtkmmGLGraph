/**
 * @file Axis.cpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief Axis implementation for graphs
 * @version 0.1
 * @date 2025-10-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Axis.hpp"

using namespace Gtkmm::GLGraph;

Gtkmm::GLGraph::Axis::Axis(AxisType type, const std::string &label, const Gdk::RGBA& color)
    : _type(type)
    , _label(label)
    , _color(color)
{}


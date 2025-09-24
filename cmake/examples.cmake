# gtkmm GL Graph examples
set(GLGRAPH_EXAMPLES_DIR ${PROJECT_SOURCE_DIR}/source/examples)
set(GLGRAPH_EXAMPLES_INCLUDE_DIRS 
    ${PROJECT_SOURCE_DIR}/source/include
)

if(GLGRAPH_BUILD_EXAMPLES)

# Sine_wave example
add_executable(sine_wave ${GLGRAPH_EXAMPLES_DIR}/sine_wave.cpp)
target_include_directories(sine_wave PRIVATE ${GLGRAPH_EXAMPLES_INCLUDE_DIRS})
target_link_libraries(
    sine_wave 
    PRIVATE 
    GtkmmGLGraph::GtkmmGLGraph 
)

endif()
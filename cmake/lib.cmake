# gtkmm GL Graph library target
set(GLGRAPH_DIR ${PROJECT_SOURCE_DIR}/source)
set(GLGRAPH_INCLUDE_DIRS 
    ${GLGRAPH_DIR}/include
)
set(GLGRAPH_SOURCE_DIR ${GLGRAPH_DIR}/src)
add_library(GtkmmGLGraph
    ${GLGRAPH_SOURCE_DIR}/GLGraph.cpp
)
target_include_directories(GtkmmGLGraph 
    PUBLIC 
    $<BUILD_INTERFACE:${GLGRAPH_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(
    GtkmmGLGraph 
    PUBLIC
    ${GTKMM_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

add_library(GtkmmGLGraph::GtkmmGLGraph ALIAS GtkmmGLGraph)
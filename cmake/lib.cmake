# gtkmm GL Graph library target
set(GLGRAPH_DIR ${PROJECT_SOURCE_DIR}/source)
set(GLGRAPH_INCLUDE_DIRS 
    ${GLGRAPH_DIR}/include
)
set(GLGRAPH_SOURCE_DIR ${GLGRAPH_DIR}/src)

# Core components
set(GLGRAPH_CORE_INCLUDE_DIRS ${GLGRAPH_INCLUDE_DIRS}/core)
set(GLGRAPH_CORE_SOURCE_DIR ${GLGRAPH_SOURCE_DIR}/core)
set(GLGRAPH_CORE_SRCS
    ${GLGRAPH_CORE_SOURCE_DIR}/Renderer.cpp
    ${GLGRAPH_CORE_SOURCE_DIR}/PlotArea.cpp
    ${GLGRAPH_CORE_SOURCE_DIR}/Shader.cpp
)

add_library(GtkmmGLGraph
    ${GLGRAPH_CORE_SRCS}
    ${GLGRAPH_SOURCE_DIR}/GLGraph.cpp
)
target_include_directories(GtkmmGLGraph 
    PUBLIC 
    ${GLGRAPH_CORE_INCLUDE_DIRS}
    ${GLGRAPH_INCLUDE_DIRS}
    ${GTKMM_INCLUDE_DIRS}
)
target_link_libraries(
    GtkmmGLGraph 
    PUBLIC
    ${GTKMM_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${EPOXY_LIBRARIES}
)

add_library(GtkmmGLGraph::GtkmmGLGraph ALIAS GtkmmGLGraph)
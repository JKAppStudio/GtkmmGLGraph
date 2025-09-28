/**
 * @file Shaders.hpp
 * @author Evgeny Krivoshein (jkappstudio@gmail.com)
 * @brief OpenGL shader management
 * @version 0.1
 * @date 2025-09-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __GTKMM_GLGRAPH_SHADERS_HPP__
#define __GTKMM_GLGRAPH_SHADERS_HPP__

#include <epoxy/gl.h>
#include <string>

namespace Gtkmm {
namespace GLGraph {

typedef struct Shader {
    Shader() : program(0) {}
    void init(const std::string& vertexSource, const std::string& fragmentSource);

    /**
     * @brief Check OpenGL shader compilation status
     * @param shader The shader object to check
     * @param type The type of shader (vertex, fragment, etc.)
     */
    static void check_shader_compile(GLuint shader, const std::string& type);

    /**
     * @brief Check OpenGL shader program linking status
     * @param program The shader program to check
     */
    static void check_program_link(GLuint program);

    GLuint program;
} Shader;

} // namespace GLGraph
} // namespace Gtkmm

#endif // !__GTKMM_GLGRAPH_SHADERS_HPP__

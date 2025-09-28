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
    attach(_plotArea, 0, 0, 1, 1);
    _plotArea.set_expand();
}

GLGraph::~GLGraph() {
    // Destructor implementation
}

/*
bool GLGraph::on_render(const Glib::RefPtr<Gdk::GLContext>& context) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_LINE_LOOP, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);

    return true;
}

void GLGraph::on_realize() {
    Gtk::GLArea::on_realize();
    make_current();

    // Check for context errors
    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "OpenGL context creation failed." << std::endl;
        return;
    }

    // Vertex shader
    const char* vertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec3 aColor;
        out vec3 vColor;
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            vColor = aColor;
        }
    )";

    // Fragment shader
    const char* fragmentShaderSrc = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);
    check_shader_compile(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);
    check_shader_compile(fragmentShader, "FRAGMENT");

    // Link program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check_program_link(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Triangle vertices: 2D position + RGB color
    float vertices[] = {
        // pos        // color
        -0.6f, -0.4f, 1.0f, 0.0f, 0.0f,
        0.6f, -0.4f, 1.0f, 0.0f, 0.0f,
        0.0f,  0.6f, 1.0f, 0.0f, 0.0f
    };

    // Generate VAO & VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Background color
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
}

void GLGraph::on_unrealize() {
    make_current();

    // Cleanup OpenGL resources
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
    if (shaderProgram) glDeleteProgram(shaderProgram);

    // Must call base implementation last
    Gtk::GLArea::on_unrealize();
}
*/
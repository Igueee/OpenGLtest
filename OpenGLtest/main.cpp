//
//  main.cpp
//  OpenGLtest
//
//  Created by Ignácio Azevedo on 02/12/25.
//

// Tell GLFW not to include any OpenGL headers for us; we will include the macOS system headers.
#define GLFW_INCLUDE_NONE

// Silence deprecation warnings for OpenGL on macOS (OpenGL is deprecated since macOS 10.14).
#define GL_SILENCE_DEPRECATION 1

// macOS system OpenGL 3.2 Core Profile headers
#include <OpenGL/gl3.h>

// GLFW for window/context creation and input/events
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    // Initialize the GLFW library. Required before any other GLFW calls.
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Request a 3.2 Core Profile OpenGL context on macOS.
    // The combination of these hints ensures we get a forward-compatible core profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);           // OpenGL major version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);           // OpenGL minor version 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core profile (no deprecated fixed-function)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     // Required on macOS to get a core profile context

    // Create a windowed mode window and its OpenGL context.
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLtest", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current on this thread.
    glfwMakeContextCurrent(window);

    // No GLAD (or GLEW) initialization needed on macOS when using system OpenGL headers.
    
    Shader ourShader("shader.vs", "shader.fs");
    
    // Define vertices
    float triangle1[] = {
        // positions        // colors
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
    };
    
    // Create Vertex Buffer Object, Vertex Array Object and Element Buffer Object
    unsigned int VBOs[1], VAOs[1];
    glGenBuffers(1, VBOs);
    glGenVertexArrays(1, VAOs);
    
    // Bind VAO 1
    glBindVertexArray(VAOs[0]);
    
    // Copy the vertices to the 1st buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    
    // Tell OpenGL how to interpret vertex data for 1st buffer
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Set the viewport to cover the whole window. Typically updated on resize.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Set drawing mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Main loop: run until the user closes the window.
    while (!glfwWindowShouldClose(window)) {
        
        // Check if user pressed escape to close the window
        processInput(window);
        
        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw Object
        ourShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Swap front and back buffers (present the frame).
        glfwSwapBuffers(window);

        // Poll for and process events (keyboard, mouse, window, etc.).
        glfwPollEvents();
    }

    // Clean up: destroy the window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

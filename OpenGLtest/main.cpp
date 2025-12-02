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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    // Initialize the GLFW library. Required before any other GLFW calls.
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Request a 3.2 Core Profile OpenGL context on macOS.
    // The combination of these hints ensures we get a forward-compatible core profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);           // OpenGL major version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);           // OpenGL minor version 2 (=> 3.2)
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
    
    // Set the viewport to cover the whole window. Typically updated on resize.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Main loop: run until the user closes the window.
    while (!glfwWindowShouldClose(window)) {

        
        // If you want to clear to a color each frame, uncomment these lines:
        // glClearColor(0.1f, 0.2f, 0.3f, 1.0f);   // RGBA clear color
        // glClear(GL_COLOR_BUFFER_BIT);           // Clear the color buffer

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


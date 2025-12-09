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
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor\n;"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";

const char *fragmentShader0Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main(){\n"
    "   FragColor = ourColor;\n"
    "}\0";

const char *fragmentShader1Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main(){\n"
    "   FragColor = ourColor;\n"
    "}\0";

int success;
char infoLog[512];
int vertexColorLocation[2];


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
    
    // Compile Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // Check if vertex shader compiled successfully
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Compile fragment shader 0
    unsigned int fragmentShader0;
    fragmentShader0 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader0, 1, &fragmentShader0Source, NULL);
    glCompileShader(fragmentShader0);
    
    // Check if fragment shader 0 compiled successfully
    glGetShaderiv(fragmentShader0, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader0, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::0::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Compile fragment shader 1
    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShader1);
    
    // Check if fragment shader 1 compiled successfully
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::1::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Create shader programs and link shaders and delete them
    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader0);
    glLinkProgram(shaderProgram[0]);
    glDeleteShader(fragmentShader0);
    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShader1);
    glLinkProgram(shaderProgram[1]);
    glDeleteShader(fragmentShader1);
    glDeleteShader(vertexShader);
    
    // Check if programs linked successfully
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::0::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::1::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Get uniform locations
    vertexColorLocation[0] = glGetUniformLocation(shaderProgram[0], "ourColor");
    vertexColorLocation[1] = glGetUniformLocation(shaderProgram[1], "ourColor");
    
    // Define vertices
    float triangle1[] = {
         0.0f, -0.5f, 0.0f, // intersection
        -0.5f,  0.5f, 0.0f, // top left
        -1.0f, -0.5f, 0.0f  // bottom left
    };
    float triangle2[] = {
        0.0f, -0.5f, 0.0f, // intersection
        0.5f,  0.5f, 0.0f, // top right
        1.0f, -0.5f, 0.0f // bottom right
    };
    
    // Create Vertex Buffer Object, Vertex Array Object and Element Buffer Object
    unsigned int VBOs[2], VAOs[2];
    glGenBuffers(2, VBOs);
    glGenVertexArrays(2, VAOs);
    
    // Bind VAO 1
    glBindVertexArray(VAOs[0]);
    
    // Copy the vertices to the 1st buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    
    // Tell OpenGL how to interpret vertex data for 1st buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Bind VAO 2
    glBindVertexArray(VAOs[1]);
    
    // Copy the vertices to the 2nd buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    
    // Tell OpenGL how to interpret vertex data for 2nd buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
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
        
        // Get shader color value based on time
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        
        // Draw Object
        glUseProgram(shaderProgram[0]);
        glUniform4f(vertexColorLocation[0], 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram[1]);
        glUniform4f(vertexColorLocation[1], 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAOs[1]);
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

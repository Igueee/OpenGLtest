//
//  shader.h
//  OpenGLtest
//
//  Created by Ignácio Azevedo on 09/12/25.
//

#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader{
public:
    // Program ID
    unsigned int ID;
    
    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath){
        // Retrive the vertex/fragment source from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions
        vShader
    };
    // Use/Activate the shader
    void use();
    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif // !SHADER_H

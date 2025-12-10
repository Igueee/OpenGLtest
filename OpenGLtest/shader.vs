//
//  vertex.vsh
//  OpenGLtest
//
//  Created by Ignácio Azevedo on 03/12/25.
//

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}

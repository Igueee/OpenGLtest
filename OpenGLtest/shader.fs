//
//  fragment.fsh
//  OpenGLtest
//
//  Created by Ignácio Azevedo on 03/12/25.
//

#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main(){
    FragColor = vec4(ourColor, 1.0f);
}

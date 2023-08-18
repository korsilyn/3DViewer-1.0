#version 330 core


layout(location = 0) in vec4 position;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main() {
//  gl_Position = projectionMatrix * modelMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * modelMatrix * position;
}

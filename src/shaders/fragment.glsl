#version 330 core
out vec4 fragColor;
uniform vec4 edgeColor;

void main() {
  fragColor = edgeColor;
}

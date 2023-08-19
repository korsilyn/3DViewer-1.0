#version 330 core


out vec4 fragColor;

uniform int vertexRenderingMode;
uniform int edgeRenderingMode;
uniform vec4 vertexColor;
uniform vec4 edgeColor;
uniform float vertexSize;
uniform float edgeThickness;

void main() {
  if (vertexRenderingMode == 1) {
    fragColor = vertexColor;
  } else if (vertexRenderingMode == 2) {
    float radius = length(gl_pointCoord - vec2(0.5, 0.5));
    if (radius > 0.5) discard;
    fragColor = vertexColor;
  } else
    discard;

  if (edgeRenderingMode == 1) {
    if (fract(gl_FragCoord.y) > 0.5) discard;
  }

  fragColor = mix(fragColor, edgeColor, 0.0);
}

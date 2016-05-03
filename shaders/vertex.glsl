#version 120

// input
attribute vec3 vertexPosition_modelspace;
attribute vec3 a_color;

// output
varying vec3 color;

// const
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main() {
  gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
  color = a_color;
}

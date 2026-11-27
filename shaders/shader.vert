#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

out vec3 color;

uniform mat4 trans;
uniform mat4 projection;
uniform mat4 view;

void main() {
    color = a_color;
    gl_Position = projection * view * trans * vec4(a_pos, 1.0);
}
#version 440 core

layout(location = 0) in vec3 a_f3Vertex_Ms;
layout(location = 1) in vec4 a_f4Color;

uniform mat4 u_m4MVP;

out vec4 v_f4Color;

void main()
{
    gl_Position = u_m4MVP * vec4(a_f3Vertex_Ms, 1.0);
    v_f4Color = a_f4Color;
}


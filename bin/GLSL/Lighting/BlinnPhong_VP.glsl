#version 440 core

layout(location = 0) in vec3 a_f3Vertex_Ms;
layout(location = 1) in vec4 a_f4Color;
layout(location = 2) in vec3 a_f3Normal_Ms_N;

uniform mat4 u_m4View = mat4(1.);
uniform mat4 u_m4MV = mat4(1.);
uniform mat4 u_m4MVP = mat4(1.);

out vec4 v_f4Vertex_Vs;
out vec4 v_f4Color;
out vec4 v_f4Normal_Vs;

void main()
{
    gl_Position = u_m4MVP * vec4(a_f3Vertex_Ms, 1.0);

    v_f4Vertex_Vs = u_m4MV * vec4(a_f3Vertex_Ms, 1.0);
    v_f4Color = a_f4Color;
    v_f4Normal_Vs = u_m4MV * vec4(a_f3Normal_Ms_N, 0.0);
}


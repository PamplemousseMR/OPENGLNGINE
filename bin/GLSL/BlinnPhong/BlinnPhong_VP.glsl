#version 440 core

layout(location = 0) in vec3 a_f3Vertex_Ms;
layout(location = 1) in vec4 a_f4Color;
layout(location = 2) in vec3 a_f3Normal_Ms_N;

uniform mat4 u_m4Model;
uniform mat4 u_m4View;
uniform mat4 u_m4Projection;

uniform vec3 u_f3LightPos_Ws;

out vec4 v_f4Vertex_Vs;
out vec4 v_f4Color;
out vec4 v_f4Normal_Vs;

out vec3 v_f3LightPos_Vs;

void main()
{
    gl_Position = u_m4Projection * u_m4View * u_m4Model * vec4(a_f3Vertex_Ms, 1.0);

    v_f4Vertex_Vs = u_m4View * u_m4Model * vec4(a_f3Vertex_Ms, 1.0);
    v_f4Color = a_f4Color;
    v_f4Normal_Vs = u_m4View * u_m4Model * vec4(a_f3Normal_Ms_N, 0.0);

    v_f3LightPos_Vs = vec4(u_m4View * vec4(u_f3LightPos_Ws, 1.0)).xyz;
}


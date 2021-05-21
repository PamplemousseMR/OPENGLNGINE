#version 440 core

layout(location = 0) in vec3 a_f3VertexPos_Ss;
layout(location = 1) in vec4 a_f4VertexCol;

uniform mat4 u_m4Model;
uniform mat4 u_m4View;
uniform mat4 u_m4Projection;

out vec4 v_f4VertexCol;

void main()
{
    gl_Position = u_m4Projection * u_m4View * u_m4Model * vec4(a_f3VertexPos_Ss, 1.0);
    v_f4VertexCol = a_f4VertexCol;
}


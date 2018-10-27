#version 440 core

layout(location = 0) in vec3 a_f3VertexPos_Ms;
layout(location = 2) in vec3 a_f3NormalDir_Ms;

uniform mat4 u_m4View;
uniform mat4 u_m4Model;
uniform mat4 u_m4Projection;

out s_vertex
{
    vec3 v_f3NormalDir_Ms;
    mat4 v_modelViewProj;
}
v_vertex;

void main()
{
    gl_Position = vec4(a_f3VertexPos_Ms, 1.0);
    v_vertex.v_f3NormalDir_Ms = a_f3NormalDir_Ms;
    v_vertex.v_modelViewProj = u_m4Projection * u_m4View * u_m4Model;
}


#version 440 core

layout(location = 0) in vec3 a_f3Vertex_Ms;
layout(location = 3) in vec2 a_f2TextCoord_Ts;

uniform mat4 u_m4MVP = mat4(1.);

out vec2 v_f2TextCoord_Ts;

void main()
{
    gl_Position = u_m4MVP * vec4(a_f3Vertex_Ms, 1.0);
    v_f2TextCoord_Ts = a_f2TextCoord_Ts;
}


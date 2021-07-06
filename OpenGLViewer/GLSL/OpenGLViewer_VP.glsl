#version 440 core

layout(location = 0) in vec3 a_f3Vertex_Ms;
layout(location = 1) in vec4 a_f4Color;
layout(location = 7) in vec3 a_f3Normal_Ms;
layout(location = 8) in vec2 a_f2TextCoord_Ts;

uniform mat4 u_m4MV = mat4(1.);
uniform mat4 u_m4MVP = mat4(1.);

out vec3 v_f3Vertex_Vs;
out vec4 v_f4Color;
out vec3 v_f3Normal_Vs;
out vec2 v_f2TextCoord_Ts;

void main()
{
    gl_Position = u_m4MVP * vec4(a_f3Vertex_Ms, 1.0);

    v_f3Vertex_Vs = (u_m4MV * vec4(a_f3Vertex_Ms, 1.0)).xyz;
    v_f4Color = a_f4Color;
    v_f3Normal_Vs = (u_m4MV * vec4(a_f3Normal_Ms, 0.0)).xyz;
    v_f2TextCoord_Ts = a_f2TextCoord_Ts;
}


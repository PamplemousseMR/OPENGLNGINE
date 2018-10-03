#version 440 core

layout(location = 0) in vec3 a_f3VertexPos_Ms;
layout(location = 1) in vec2 a_f2TextCor_Fs;
layout(location = 2) in vec3 a_f3NormalDir_Ms;

uniform mat4 u_m4View;
uniform mat4 u_m4Model;
uniform mat4 u_m4Projection;

out vec2 v_f2TextCor_Fs;
out vec3 v_f3NormalDir_Vs;
out vec3 v_f3PositionCor_Vs;

void main()
{
    gl_Position = u_m4Projection * u_m4View * u_m4Model * vec4(a_f3VertexPos_Ms, 1.0);

    v_f3NormalDir_Vs = ( u_m4View * u_m4Model * vec4(a_f3NormalDir_Ms,0)).xyz;

    v_f2TextCor_Fs = a_f2TextCor_Fs;

    v_f3PositionCor_Vs = (u_m4View * u_m4Model * vec4(a_f3VertexPos_Ms, 1.0)).xyz;
}


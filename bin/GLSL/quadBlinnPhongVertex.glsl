#version 440 core

layout(location = 0) in vec3 a_f3VertexPos_Ms;

uniform vec3 u_f3LightPos_Ws;

void main()
{
    gl_Position = vec4(a_f3VertexPos_Ms,1);
}

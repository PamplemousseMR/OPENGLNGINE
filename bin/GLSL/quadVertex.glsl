#version 440 core

layout(location = 0) in vec3 a_f3VertexPos_Ms;

out vec2 v_f2TextCor;

void main()
{
    gl_Position = vec4(a_f3VertexPos_Ms,1);

    v_f2TextCor = a_f3VertexPos_Ms.xy;
}


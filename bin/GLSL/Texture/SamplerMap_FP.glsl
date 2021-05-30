#version 440 core

uniform sampler2D u_s2Texture;

in vec2 v_f2TextCoord_Ts;

out vec3 f_f3OutCol;

void main()
{
    f_f3OutCol = texture(u_s2Texture, v_f2TextCoord_Ts).rgb;
}


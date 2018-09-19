#version 440 core

in vec2 v_f2TextCor;

uniform sampler2D u_tTexture;

out vec4 v_f4OutCol;

void main()
{
    v_f4OutCol = texture(u_tTexture, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5));
}

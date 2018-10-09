#version 440 core

in vec2 v_f2TextCor_Fs;
in vec3 v_f3NormalDir_Vs;
in vec3 v_f3PositionCor_Vs;

uniform bool u_bAmbient;
uniform bool u_bDiffuse;
uniform bool u_bSpecular;

uniform sampler2D u_tAmbient;
uniform sampler2D u_tDiffuse;
uniform sampler2D u_tSpecular;

uniform float u_fSpecularExponent;
uniform vec3 u_f3AmbientCol;
uniform vec3 u_f3DiffuseCol;
uniform vec3 u_f3SpecularCol;

layout(location = 0) out vec3 v_f3OutPositionCor_Vs;
layout(location = 1) out vec4 v_f4OutNormalDir_Vs;
layout(location = 2) out vec3 v_f3OutAmbientCol_Vs;
layout(location = 3) out vec3 v_f3OutDiffuseCol_Vs;
layout(location = 4) out vec3 v_f3OutSpecularCol_Vs;

void main()
{
    vec3 f3AmbientCol = vec3(0.25, 0.25, 0.25);
    vec3 f3DiffuseCol = vec3(0.25, 0.25, 0.25);
    vec3 f3SpecularCol = vec3(0.25, 0.25, 0.25);

    // ambient
    if(u_bAmbient)
    {
        f3AmbientCol = texture( u_tAmbient, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y)).rgb;
    }

    // diffuse
    if(u_bDiffuse)
    {
        f3DiffuseCol = texture( u_tDiffuse, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y)).rgb;
    }

    // specular
    if(u_bSpecular)
    {
        f3SpecularCol = texture( u_tSpecular, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y)).rgb;
    }

    v_f3OutPositionCor_Vs = v_f3PositionCor_Vs;
    v_f4OutNormalDir_Vs = vec4(v_f3NormalDir_Vs, u_fSpecularExponent);
    v_f3OutAmbientCol_Vs = f3AmbientCol * u_f3AmbientCol;
    v_f3OutDiffuseCol_Vs = f3DiffuseCol * u_f3DiffuseCol;
    v_f3OutSpecularCol_Vs = f3SpecularCol * u_f3SpecularCol;
}

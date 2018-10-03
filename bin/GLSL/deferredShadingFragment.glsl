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
layout(location = 2) out vec4 v_f4OutAmbientCol_Vs;
layout(location = 3) out vec4 v_f4OutDiffuseCol_Vs;
layout(location = 4) out vec4 v_f4OutSpecularCol_Vs;

void main()
{
    vec4 f4AmbientCol = vec4(0.25, 0.25, 0.25, 1.0);
    vec4 f4DiffuseCol = vec4(0.25, 0.25, 0.25, 1.0);
    vec4 f4SpecularCol = vec4(0.25, 0.25, 0.25, 1.0);

    // ambient
    if(u_bAmbient)
    {
        f4AmbientCol = texture( u_tAmbient, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y));
    }

    // diffuse
    if(u_bDiffuse)
    {
        f4DiffuseCol = texture( u_tDiffuse, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y));
    }

    // specular
    if(u_bSpecular)
    {
        f4SpecularCol = texture( u_tSpecular, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y));
    }

    v_f3OutPositionCor_Vs = v_f3PositionCor_Vs;
    v_f4OutNormalDir_Vs = vec4(v_f3NormalDir_Vs, u_fSpecularExponent);
    v_f4OutAmbientCol_Vs = f4AmbientCol * vec4(u_f3AmbientCol, 1.0);
    v_f4OutDiffuseCol_Vs = f4DiffuseCol * vec4(u_f3DiffuseCol, 1.0);
    v_f4OutSpecularCol_Vs = f4SpecularCol * vec4(u_f3SpecularCol, 1.0);
}

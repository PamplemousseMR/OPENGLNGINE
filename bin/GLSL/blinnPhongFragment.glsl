#version 440 core

in vec2 v_f2TextCor_Fs;
in vec3 v_f3NormalDir_Vs;
in vec3 v_f3CamDir_Vs;
in vec3 v_f3LightDir_Vs;

uniform sampler2D u_tAmbient;
uniform sampler2D u_tDiffuse;
uniform sampler2D u_tSpecular;
uniform sampler2D u_tNormal;

uniform bool u_bAmbient;
uniform bool u_bDiffuse;
uniform bool u_bSpecular;
uniform bool u_bNormal;

uniform float u_fSpecularExponent;
uniform vec3 u_f3AmbientCol;
uniform vec3 u_f3SpecularCol;
uniform vec3 u_f3DiffuseCol;

uniform vec3 u_f3LightCol;

out vec4 v_f4OutCol;

void main()
{
    vec3 f3AmbientCol = vec3(0.25,0.25,0.25);
    vec3 f3DiffuseCol = vec3(0.25,0.25,0.25);
    vec3 f3SpecularCol = vec3(0.25,0.25,0.25);
    float fAlpha = 1.0f;

    vec3 f3NormalDir_VsN = normalize(v_f3NormalDir_Vs);
    vec3 f3LightDir_VsN = normalize(v_f3LightDir_Vs);
    float cosTheta = clamp( dot(f3NormalDir_VsN, f3LightDir_VsN), 0, 1);
    vec3 f3CamDir_VsN = normalize(v_f3CamDir_Vs);
    vec3 f3CamReflectDir_VsN = reflect(-f3LightDir_VsN,f3NormalDir_VsN);
    float cosAlpha = clamp(dot(f3CamDir_VsN, f3CamReflectDir_VsN), 0, 1);

    // ambient
    if(u_bAmbient)
    {
        f3AmbientCol = texture( u_tAmbient, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y)).rgb;
    }

    // diffuse    
    if(u_bDiffuse)
    {
        vec4 f4DiffuseCol = texture( u_tDiffuse, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y));
        f3DiffuseCol = f4DiffuseCol.rgb;
        fAlpha = f4DiffuseCol.a;
    }
    f3DiffuseCol = f3DiffuseCol * u_f3LightCol * cosTheta;

    // specular
    if(u_bSpecular)
    {
        f3SpecularCol = texture( u_tSpecular, vec2(v_f2TextCor_Fs.x, 1 - v_f2TextCor_Fs.y)).rgb;
    }
    f3SpecularCol = f3SpecularCol * u_f3LightCol * pow(cosAlpha,u_fSpecularExponent);

    v_f4OutCol = vec4(u_f3AmbientCol*f3AmbientCol + u_f3DiffuseCol*f3DiffuseCol + u_f3SpecularCol*f3SpecularCol ,fAlpha);
}

#version 440 core

#define MAX_LIGHT_COUNT 10

uniform uint u_uiLightCount = 0;
uniform vec4 u_f4LightPos_Vs[MAX_LIGHT_COUNT];
uniform vec3 u_f3LightAmbient[MAX_LIGHT_COUNT];
uniform vec3 u_f3LightDiffuse[MAX_LIGHT_COUNT];
uniform vec3 u_f3LightSpecular[MAX_LIGHT_COUNT];

uniform float u_ns = 32.f;

in vec4 v_f4Vertex_Vs;
in vec4 v_f4Color;
in vec4 v_f4Normal_Vs;

in vec3 v_f3LightDir_Vs;

out vec4 f_f4OutCol;

void main()
{
    vec3 f3AmbientCol = vec3(0.);
    vec3 f3DiffuseCol = vec3(0.);
    vec3 f3SpecularCol = vec3(0.);

    for(uint i=0 ; i<u_uiLightCount && i<MAX_LIGHT_COUNT ; ++i)
    {
        vec3 f3CamDir_VsN = normalize(vec3(0.) - v_f4Vertex_Vs.xyz);

        vec3 f3LightDir_VsN = normalize(u_f4LightPos_Vs[i].w * v_f4Vertex_Vs.xyz - u_f4LightPos_Vs[i].xyz);

        vec3 f3NormalDir_VsN = normalize(v_f4Normal_Vs).xyz;

        float cosTheta = clamp( dot(f3NormalDir_VsN, -f3LightDir_VsN), 0, 1);
        vec3 f3CamReflectDir_VsN = reflect(f3LightDir_VsN,f3NormalDir_VsN);
        float cosAlpha = clamp(dot(f3CamDir_VsN, f3CamReflectDir_VsN), 0, 1);

        f3AmbientCol += u_f3LightAmbient[i] * v_f4Color.xyz;
        f3DiffuseCol += u_f3LightDiffuse[i] * vec3(v_f4Color.xyz * cosTheta);
        f3SpecularCol += u_f3LightSpecular[i] * pow(cosAlpha, u_ns);
    }


    f_f4OutCol = vec4(f3AmbientCol + f3DiffuseCol + f3SpecularCol, v_f4Color.a);
}


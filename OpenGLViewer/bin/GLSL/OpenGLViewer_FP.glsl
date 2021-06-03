#version 440 core

#define MAX_LIGHT_COUNT 10

uniform uint u_uiLightCount = 0;
uniform vec4 u_f4LightPos_Vs[MAX_LIGHT_COUNT];
uniform vec3 u_f3LightDiffuse[MAX_LIGHT_COUNT];
uniform vec3 u_f3LightSpecular[MAX_LIGHT_COUNT];

uniform vec3 u_f3Ambient = vec3(1.f);
uniform vec3 u_f3Diffuse = vec3(1.f);
uniform vec3 u_f3Specular = vec3(1.f);

uniform float u_fShininess = 1.f;

uniform sampler2D u_s2Ambient;
uniform float u_fHasAmbient = 0.f;
uniform sampler2D u_s2Diffuse;
uniform float u_fHasDiffuse = 0.f;
uniform sampler2D u_s2Specular;
uniform float u_fHasSpecular = 0.f;

in vec3 v_f3Vertex_Vs;
in vec4 v_f4Color;
in vec3 v_f3Normal_Vs;
in vec2 v_f2TextCoord_Ts;

out vec4 f_f4OutCol;

void main()
{
    vec3 f3AmbientCol = u_f3Ambient * (u_fHasAmbient * texture(u_s2Ambient, v_f2TextCoord_Ts).rgb + (1 - u_fHasAmbient));

    vec3 f3DiffuseCol = vec3(0.);
    vec3 f3SpecularCol = vec3(0.);
    vec3 f3MaDiffuse = u_fHasDiffuse * texture(u_s2Diffuse, v_f2TextCoord_Ts).rgb + (1 - u_fHasDiffuse);
    vec3 f3MaSpecular = u_fHasSpecular * texture(u_s2Specular, v_f2TextCoord_Ts).rgb + (1 - u_fHasSpecular);

    for(uint i=0 ; i<u_uiLightCount && i<MAX_LIGHT_COUNT ; ++i)
    {
        vec3 f3CamDir_VsN = normalize(vec3(0.) - v_f3Vertex_Vs);

        vec3 f3LightDir_VsN = normalize(u_f4LightPos_Vs[i].w * v_f3Vertex_Vs - u_f4LightPos_Vs[i].xyz);

        vec3 f3NormalDir_VsN = normalize(v_f3Normal_Vs);

        float cosTheta = clamp( dot(f3NormalDir_VsN, -f3LightDir_VsN), 0, 1);
        vec3 f3CamReflectDir_VsN = reflect(f3LightDir_VsN,f3NormalDir_VsN);
        float cosAlpha = clamp(dot(f3CamDir_VsN, f3CamReflectDir_VsN), 0, 1);

        f3DiffuseCol += u_f3Diffuse * u_f3LightDiffuse[i] * vec3(f3MaDiffuse * cosTheta);
        f3SpecularCol += u_f3Specular * f3MaSpecular * u_f3LightSpecular[i] * pow(cosAlpha, u_fShininess);
    }

    f_f4OutCol = vec4(f3AmbientCol + f3DiffuseCol + f3SpecularCol, v_f4Color.a);
}


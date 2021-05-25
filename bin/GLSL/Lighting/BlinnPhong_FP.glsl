#version 440 core

uniform vec3 u_f3LightAmbient = vec3(1., 1., 1.);
uniform vec3 u_f3LightDiffuse = vec3(1., 1., 1.);
uniform vec3 u_f3LightSpecular = vec3(1., 1., 1.);

uniform float u_ns = 32.f;

in vec4 v_f4Vertex_Vs;
in vec4 v_f4Color;
in vec4 v_f4Normal_Vs;

in vec3 v_f3LightDir_Vs;

out vec4 f_f4OutCol;

void main()
{
    vec3 f3CamDir_VsN = normalize(vec3(0.0, 0.0, 0.0) - v_f4Vertex_Vs.xyz);

    vec3 f3LightDir_VsN = normalize(v_f3LightDir_Vs);

    vec3 f3NormalDir_VsN = normalize(v_f4Normal_Vs).xyz;

    float cosTheta = clamp( dot(f3NormalDir_VsN, -f3LightDir_VsN), 0, 1);
    vec3 f3CamReflectDir_VsN = reflect(f3LightDir_VsN,f3NormalDir_VsN);
    float cosAlpha = clamp(dot(f3CamDir_VsN, f3CamReflectDir_VsN), 0, 1);

    vec3 f3AmbientCol = u_f3LightAmbient * v_f4Color.xyz;

    vec3 f3DiffuseCol = u_f3LightDiffuse * vec3(v_f4Color.xyz * cosTheta);

    vec3 f3SpecularCol = u_f3LightSpecular * pow(cosAlpha, u_ns);

    f_f4OutCol = vec4(f3AmbientCol + f3DiffuseCol + f3SpecularCol, v_f4Color.a);
}


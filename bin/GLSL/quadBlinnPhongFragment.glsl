#version 440 core

in vec2 v_f2TextCor;

uniform sampler2DMS u_tPositionCor_Vs;
uniform sampler2DMS u_tNormalDir_Vs;
uniform sampler2DMS u_tAmbientCol_Vs;
uniform sampler2DMS u_tDiffuseCol_Vs;
uniform sampler2DMS u_tSpecularCol_Vs;
uniform sampler2DMS u_tSpecularExp;

uniform mat4 u_m4View;
uniform vec3 u_f3LightPos_Ws;
uniform vec3 u_f3LightCol;

uniform vec2 u_viewport;
uniform int u_sample;

out vec3 v_f3OutCol;

void main()
{
    vec3 f3AmbientCol = vec3(0.0, 0.0, 0.0);
    vec3 f3DiffuseCol = vec3(0.0, 0.0, 0.0);
    vec3 f3SpecularCol = vec3(0.0, 0.0, 0.0);

    for(int sampler = 0 ; sampler < u_sample ; ++sampler)
    {
        vec3 f3CamDir_VsN = normalize(vec3(0,0,0) - texelFetch(u_tPositionCor_Vs, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).xyz);

        vec3 lightPos_Vs = ( u_m4View * vec4(u_f3LightPos_Ws,1)).xyz;
        vec3 v_f3LightDir_Vs = lightPos_Vs - texelFetch(u_tPositionCor_Vs, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).xyz;
        vec3 f3LightDir_VsN = normalize(v_f3LightDir_Vs);

        vec3 f3NormalDir_VsN = normalize(texelFetch(u_tNormalDir_Vs, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).xyz);

        float cosTheta = clamp( dot(f3NormalDir_VsN, f3LightDir_VsN), 0, 1);
        vec3 f3CamReflectDir_VsN = reflect(-f3LightDir_VsN,f3NormalDir_VsN);
        float cosAlpha = clamp(dot(f3CamDir_VsN, f3CamReflectDir_VsN), 0, 1);

        f3AmbientCol += texelFetch(u_tAmbientCol_Vs, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).rgb;

        vec3 f3DiffuseColTmp = texelFetch(u_tDiffuseCol_Vs, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).rgb;
        f3DiffuseCol += f3DiffuseColTmp * u_f3LightCol * cosTheta;

        vec3 f3SpecularColTmp = texelFetch(u_tSpecularCol_Vs, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).rgb;
        float fSpecularExponent = texelFetch(u_tSpecularExp, ivec2((v_f2TextCor.x+1) * 0.5 * u_viewport.x, (v_f2TextCor.y+1) * 0.5 * u_viewport.y), sampler).x;
        f3SpecularCol += f3SpecularColTmp * u_f3LightCol * pow(cosAlpha, fSpecularExponent);
    }

    v_f3OutCol = (f3AmbientCol + f3DiffuseCol + f3SpecularCol) / u_sample;
}

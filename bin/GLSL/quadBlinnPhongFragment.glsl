#version 440 core

in vec2 v_f2TextCor;

uniform sampler2D u_tPositionCor_Vs;
uniform sampler2D u_tNormalDir_Vs;
uniform sampler2D u_tAmbientCol_Vs;
uniform sampler2D u_tDiffuseCol_Vs;
uniform sampler2D u_tSpecularCol_Vs;

uniform mat4 u_m4View;
uniform vec3 u_f3LightPos_Ws;
uniform vec3 u_f3LightCol;

out vec4 v_f4OutCol;

void main()
{
    vec3 f3CamDir_VsN = normalize(vec3(0,0,0) - texture(u_tPositionCor_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).xyz);

    vec3 lightPos_Vs = ( u_m4View * vec4(u_f3LightPos_Ws,1)).xyz;
    vec3 v_f3LightDir_Vs = lightPos_Vs - texture(u_tPositionCor_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).xyz;
    vec3 f3LightDir_VsN = normalize(v_f3LightDir_Vs);

    vec3 f3NormalDir_VsN = normalize(texture(u_tNormalDir_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).xyz);

    float cosTheta = clamp( dot(f3NormalDir_VsN, f3LightDir_VsN), 0, 1);
    vec3 f3CamReflectDir_VsN = reflect(-f3LightDir_VsN,f3NormalDir_VsN);
    float cosAlpha = clamp(dot(f3CamDir_VsN, f3CamReflectDir_VsN), 0, 1);

    vec3 f3AmbientCol = texture(u_tAmbientCol_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).rgb;

    vec3 f3DiffuseCol = texture(u_tDiffuseCol_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).rgb;
    f3DiffuseCol = f3DiffuseCol * u_f3LightCol * cosTheta;

    vec3 f3SpecularCol = texture(u_tSpecularCol_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).rgb;
    float fSpecularExponent = texture(u_tNormalDir_Vs, vec2((v_f2TextCor.x+1) * 0.5, (v_f2TextCor.y+1) * 0.5)).w;
    f3SpecularCol = f3SpecularCol * u_f3LightCol * pow(cosAlpha, fSpecularExponent);

    v_f4OutCol = vec4(f3AmbientCol + f3DiffuseCol + f3SpecularCol, 1.0);
}

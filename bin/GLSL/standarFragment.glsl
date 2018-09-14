#version 460 core

in vec2 v_textCoord;
in vec3 v_normal_cameraspace;
in vec3 v_eyeDirection_cameraspace;
in vec3 v_lightDirection_cameraspace;

uniform sampler2D u_ambientTexture;
uniform sampler2D u_diffuseTexture;
uniform sampler2D u_specularTexture;
uniform sampler2D u_normalTexture;

uniform bool u_hasAmbientTexture;
uniform bool u_hasDiffuseTexture;
uniform bool u_hasSpecularTexture;
uniform bool u_hasNormalTexture;

uniform float u_specularExponent;
uniform vec3 u_ambient;
uniform vec3 u_specular;
uniform vec3 u_diffuse;
uniform vec3 u_lightColor;

out vec4 v_color;

void main()
{
    vec3 ambient = vec3(0.25,0.25,0.25);
    vec3 diffuse = vec3(0.25,0.25,0.25);
    vec3 specular = vec3(0.25,0.25,0.25);
    float alpha = 1.0f;

    // ambient

    if(u_hasAmbientTexture)
    {
        ambient = texture( u_ambientTexture, vec2(v_textCoord.x, 1 - v_textCoord.y)).rgb;
    }

    // diffuse

    vec3 n = normalize( v_normal_cameraspace );
    vec3 l = normalize( v_lightDirection_cameraspace );
    float cosTheta = clamp( dot( n,l ), 0,1 );

    if(u_hasDiffuseTexture)
    {
        vec4 materialDiffuseColor = texture( u_diffuseTexture, vec2(v_textCoord.x, 1 - v_textCoord.y));
        diffuse = materialDiffuseColor.rgb * u_lightColor * cosTheta;
        alpha = materialDiffuseColor.a;
    }
    else
    {
        diffuse = diffuse * u_lightColor * cosTheta;
    }

    // specular

    vec3 E = normalize(v_eyeDirection_cameraspace);
    vec3 R = reflect(-l,n);
    float cosAlpha = clamp( dot( E,R ), 0,1 );

    if(u_hasSpecularTexture)
    {
        vec3 materialSpecularColor = texture( u_specularTexture, vec2(v_textCoord.x, 1 - v_textCoord.y)).xyz;
        specular = materialSpecularColor * u_lightColor * pow(cosAlpha,u_specularExponent);
    }
    else
    {
        specular = specular * u_lightColor * pow(cosAlpha,u_specularExponent);
    }

    /*color = vec4(v_normal_cameraspace,1);*/

    v_color = vec4(u_ambient*ambient + u_diffuse*diffuse + u_specular*specular ,alpha);

    /*color = vec4(materialDiffuseColor.rgb, materialDiffuseColor.a);*/
}

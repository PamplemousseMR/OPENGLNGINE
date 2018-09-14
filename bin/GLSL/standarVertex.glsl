#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_textCoord;
layout(location = 2) in vec3 a_normal;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform vec3 u_lightPosition_worldspace;

out vec2 v_textCoord;
out vec3 v_normal_cameraspace;
out vec3 v_eyeDirection_cameraspace;
out vec3 v_lightDirection_cameraspace;

void main(){ 

    gl_Position = u_projection * u_view * u_model * vec4(a_position,1);

    vec3 vertexPosition_cameraspace = ( u_view * u_model * vec4(a_position,1)).xyz;
    v_eyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

    vec3 lightPosition_cameraspace = ( u_view * vec4(u_lightPosition_worldspace,1)).xyz;
    v_lightDirection_cameraspace = lightPosition_cameraspace-vertexPosition_cameraspace;

    v_normal_cameraspace = ( u_view * u_model * vec4(a_normal,0)).xyz;

    v_textCoord = a_textCoord;
}


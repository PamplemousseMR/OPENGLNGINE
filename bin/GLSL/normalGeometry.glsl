#version 440

layout(triangles) in;
layout(line_strip, max_vertices=6) out;

in s_vertex
{
    vec3 v_f3NormalDir_Ms;
    mat4 v_modelViewProj;
}
v_vertex[];

void main()
{
    int i;
    for(i=0; i<gl_in.length(); ++i)
    {
        vec3 P = gl_in[i].gl_Position.xyz;
        vec3 N = v_vertex[i].v_f3NormalDir_Ms;

        gl_Position = v_vertex[i].v_modelViewProj * vec4(P, 1.0);
        EmitVertex();

        gl_Position = v_vertex[i].v_modelViewProj * vec4(P + N, 1.0);
        EmitVertex();

        EndPrimitive();
    }
}

#version 440

layout(triangles) in;
layout(line_strip, max_vertices=6) out;

in s_vertex
{
    vec3 v_f3NormalDir_MsN;
    mat4 v_modelViewProj;
}
v_vertex[];

void main()
{
    int i;
    for(i=0; i<gl_in.length(); ++i)
    {
        vec4 P = gl_in[i].gl_Position;
        vec3 N = v_vertex[i].v_f3NormalDir_MsN;

        gl_Position = v_vertex[i].v_modelViewProj * P;
        EmitVertex();

        gl_Position = v_vertex[i].v_modelViewProj * (P + vec4(N, 0.0));
        EmitVertex();

        EndPrimitive();
    }
}

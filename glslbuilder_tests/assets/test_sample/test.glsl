#version 450 core

#pragma type(vs_main)

layout(location = 0) in vec3 POSITION;
layout(location = 1) in vec4 COLOR;

out vec4 v_Color;

void main()
{
    gl_Position = vec4(POSITION, 1.0f);
    v_Color = COLOR;
}

#pragma endtype

#pragma type(ps_main)

layout(location = 0) out vec4 o_Color;

void main()
{
    o_Color = v_Color;
}

#pragma endtype

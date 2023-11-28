// Basic Texture Shader

#version 450 core

#pragma type(vs_main)

layout(location = 0) in vec3 POSITION;
layout(location = 1) in vec2 TEXCOORD;

layout (std140, binding = 0) uniform Matrices
{
	mat4 u_ViewProjection;
	mat4 u_Transform;
};

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = vec4(a_Position, 1.0) * u_Transform * u_ViewProjection;
}

#pragma endtype

#pragma type(ps_main)

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

layout (std140, binding = 1) uniform Color
{
	vec4 u_Color;
};

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord * 10.0) * u_Color;
}

#pragma endtype
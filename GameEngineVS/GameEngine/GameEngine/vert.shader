#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
//layout(location = 1) in vec3 aColor;

out vec2 TexCoord;
//out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 transform;


void main()
{
	//gl_Position = transform*vec4(aPos, 1.0);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
#version 450

out vec4 FragColor;
//in vec2 tc;
//out vec4 color;

//uniform mat4 mv_matrix;
//uniform mat4 proj_matrix;
//layout(binding = 0) uniform sampler2D s;

void main(void)
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//color = texture(s, tc);
}
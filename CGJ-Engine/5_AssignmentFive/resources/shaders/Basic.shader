#shader vertex
#version 410 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform mat4 MVP;

void main(void)
{
	gl_Position = Projection * View * Model * in_Position;
	ex_Color = in_Color;
}

#shader fragment
#version 410 core

in vec4 ex_Color;
out vec4 out_Color;

uniform int isBack;

void main(void)
{
	if (isBack == 0) {
		out_Color = ex_Color;
	}
	else {
		out_Color = ex_Color * 0.5f;
	}
}
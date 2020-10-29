#shader vertex
#version 410 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 Matrix;

void main(void)
{
	gl_Position = Matrix * in_Position;
	ex_Color = in_Color;
}

#shader fragment
#version 410 core

in vec4 ex_Color;
out vec4 out_Color;

uniform int isUniformColour;
uniform vec4 uniformColour;

void main(void)
{
	if (isUniformColour == 1) {
		out_Color = uniformColour;
	}
	else {
		out_Color = ex_Color;
	}
}
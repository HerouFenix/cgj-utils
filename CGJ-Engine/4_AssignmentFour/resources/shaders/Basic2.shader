#shader vertex
#version 330 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 Model;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * Model * in_Position;
	ex_Color = in_Color;
}

#shader fragment
#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

uniform int isBack;
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

	if (isBack != 0) {
		out_Color = out_Color * 0.5f;
	}

}
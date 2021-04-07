#version 450

in vec3 aPos;

out vec3 localPosition;

uniform mat4 mvpMatrix;

void main()
{
	vec4 transformedPosition = vec4(aPos.xyz, 1);
	transformedPosition = mvpMatrix * transformedPosition;

	gl_Position = transformedPosition;

	localPosition = aPos;
}

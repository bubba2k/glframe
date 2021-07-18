#version 450

in vec3 aPos;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 localPosition;
out vec3 localNormal;
out vec2 localTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vec4 transformedPosition = vec4(aPos.xyz, 1);
	transformedPosition = mvpMatrix * transformedPosition;

	gl_Position = transformedPosition;

	localPosition = aPos;
}

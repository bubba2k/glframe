#version 450

in  vec3 localPosition;
out vec4 FragColor;

void main()
{
	vec3 vecNormalizeMult = vec3(0.5, 0.5, 0.5);
	vec3 vecNormalizeAdd  = vec3(0.5, 0.5, 0.5);

	FragColor = vec4((localPosition * vecNormalizeMult + vecNormalizeAdd).xyz, 1);
}

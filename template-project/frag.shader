#version 450

in  vec3 localPosition;
in  vec3 localNormal;
in  vec2 localTexCoord;

uniform sampler2D theTexture;
uniform bool hasTexture;

out vec4 FragColor;

void main()
{
	vec3 vecNormalizeMult = vec3(0.5, 0.5, 0.5);
	vec3 vecNormalizeAdd  = vec3(0.5, 0.5, 0.5);
	
	vec3 color;


	if(hasTexture)
	{
		FragColor = texture(theTexture, localTexCoord);
	}
	else
	{
		FragColor = vec4((localPosition * vecNormalizeMult) + vecNormalizeAdd, 1);
	}
}

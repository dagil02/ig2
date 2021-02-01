#version 330 core

uniform sampler2D texturaL;
uniform sampler2D texturaM;
uniform vec4 InColor;
uniform vec4 OutColor;
uniform float Flipping;
uniform vec4 lightPosition;
uniform vec3 lightDiffuse;
uniform vec3 materialDiffuse;

in vec2 vUv0;
in vec3 vVertex;
in vec3 vNormal;

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz;
	if(lightPosition.w == 1)	//Positional
		lightDir = lightPosition.xyz - cVertex;
	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main()
{
	vec3 color;
	vec3 colorM = vec3(texture(texturaM, vUv0));
	vec3 colorL = vec3(texture(texturaL, vUv0));
	
	vec3 diffuseOut = diff(vVertex, vNormal) * lightDiffuse * materialDiffuse;
	vec3 diffuseIn = diff(vVertex, -vNormal) * lightDiffuse * materialDiffuse;

	if(colorM.r > 0.6)
	{
		discard;
	}
	
	bool frontFacing = (Flipping == -1)? !gl_FrontFacing : gl_FrontFacing;

	if(frontFacing)
	{
		color = vec3(OutColor) * colorL * diffuseOut;
	}	
	else
	{
		color = vec3(InColor) * diffuseIn;
	}
	
	fFragColor = vec4(color, 1.0);
}
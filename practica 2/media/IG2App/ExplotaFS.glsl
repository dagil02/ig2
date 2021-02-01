#version 330 core

uniform sampler2D texturaM;
uniform sampler2D texturaL;
uniform float Flipping;

out vec4 fFragColor;

uniform vec4 lightPosition;
uniform vec3 lightDiffuse;
uniform vec3 materialDiffuse;

in salidaGS
{
	vec2 vUv0; 
	vec3 vWNormal;
	vec3 vWVertex;
} entrada;

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
	vec3 colorM = vec3(texture(texturaM, entrada.vUv0));
	vec3 colorL = vec3(texture(texturaL, entrada.vUv0));
	
	vec3 diffuseOut = diff(entrada.vWVertex, entrada.vWNormal) * lightDiffuse * materialDiffuse;
	vec3 diffuseIn = diff(entrada.vWVertex, -entrada.vWNormal) * lightDiffuse * materialDiffuse;
	
	bool frontFacing = (Flipping == -1)? !gl_FrontFacing : gl_FrontFacing;

	if(frontFacing)
	{
		color =  colorM * diffuseOut;
	}	
	else
	{
		color = colorL * diffuseIn;
	}
	
	fFragColor = vec4(color, 1.0);
	
}




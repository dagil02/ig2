#version 330 core

uniform sampler2D textura0;
uniform sampler2D textura1;
uniform vec4 InColor;
uniform vec4 OutColor;
uniform float Flipping;

out vec4 fFragColor;

uniform vec3 lightPosition;
uniform vec3 lightDiffuse;

in salidaGS
{
	vec2 vUv0; 
	vec3 vWNormal;
	vec3 vWVertex;
} entrada;

void main(){
	vec3 norm = normalize(entrada.vWNormal);
	//vec3 color1 = vec3(texture(textura1, entrada.vUv0));
	
	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;
	
	if(frontFacing){
		
		float diff = max(dot(norm,lightPosition),0.0);
		vec3 diffuse = diff*lightDiffuse;
		vec3 result0 = diffuse * texture(textura0, entrada.vUv0).rgb;
		
		fFragColor = OutColor * vec4(result0,1);
		
	} else {
		
		float diff = max(dot(-norm,lightPosition),0.0);
		vec3 diffuse = diff*lightDiffuse;
		vec3 result1 = diffuse * texture(textura1, entrada.vUv0).rgb;;
		fFragColor = InColor * vec4(result1,1);
	}
	
}




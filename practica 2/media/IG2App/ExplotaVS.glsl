#version 330 core

in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewMat; 		
uniform mat4 normalMat; 		


out salidaVS{
	vec2 vUv0; 
	vec3 vWNormal; 	
	vec3 vWVertex; 	
} salida;

void main(){

	salida.vUv0 = uv0;
	salida.vWNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));
	salida.vWVertex = vec3(modelViewMat * vertex);

	gl_Position = vertex;
}

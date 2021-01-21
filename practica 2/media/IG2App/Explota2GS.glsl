#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 modelViewProjMat;
const float VD = 50;
uniform float tiempo;
uniform float tiempo2pi;

in salidaVS
{
	vec2 vUv0; 
	vec3 vWNormal;
	vec3 vWVertex; 
} entrada[];

out salidaGS
{
	vec2 vUv0; 
	vec3 vWNormal;
	vec3 vWVertex;
} salida;


void main(){
	vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
							   gl_in[1].gl_Position.xyz,			
							   gl_in[2].gl_Position.xyz);
							   
	
	vec3 baricentro = (vertices[0] + vertices[1] + vertices[2])/3;
	
	vec3 dir = normalize(baricentro);
	
	for (int i = 0; i<3; ++i){
		vec3 posDes = vertices[i] + dir * VD * tiempo;
		
		vec3 giro;
		giro.x = posDes.x * (cos(tiempo2pi)) + posDes.z * (-sin(tiempo2pi));
		giro.y = posDes.y;
		giro.z = posDes.x * (sin(tiempo2pi)) + posDes.z * (cos(tiempo2pi));
		
		gl_Position = modelViewProjMat * vec4(giro, 1.0);
		
		salida.vUv0 = entrada[i].vUv0; 
		salida.vWNormal = normalize(giro);
		salida.vWVertex = entrada[i].vWVertex;

		EmitVertex();
	}
	
	EndPrimitive();
}

#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 modelViewProjMat;
const float VD = 5;
uniform float tiempo;

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

vec3 normalVec(vec3 vertex[3]) {
	
	vec3 u = vertex[1] - vertex[0];
	vec3 v = vertex[2] - vertex[0];

	float normalX = (u.y * v.z) - (u.z * v.y);
	float normalY = (u.z * v.x) - (u.x * v.z);
	float normalZ = (u.x * v.y) - (u.y * v.x);

	return vec3(normalX, normalY, normalZ);

}

void main(){
	vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
							   gl_in[1].gl_Position.xyz,			
							   gl_in[2].gl_Position.xyz);
							   
	vec3 dir = normalVec (vertices) * tiempo;
	
	for (int i = 0; i<3; ++i){
		vec3 posDes = vertices[i] + dir * VD;
		
		gl_Position = modelViewProjMat * vec4(posDes, 1.0);
		
		salida.vUv0 = entrada[i].vUv0; 
		salida.vWNormal = entrada[i].vWNormal;
		salida.vWVertex = entrada[i].vWVertex;

		EmitVertex();
	}
	
	EndPrimitive();
}

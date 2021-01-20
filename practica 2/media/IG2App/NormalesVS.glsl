#version 330 core

in vec4 vertex;
in vec3 normal; 

out vec3 gNormal; 

void main() {

	gNormal = normalize(normal); 
	gl_Position = vertex;

} 

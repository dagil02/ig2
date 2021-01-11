#version 330 core

in vec4 vertex;
in vec3 normal;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform mat4 model; 
  
out vec2 vUv0;
out vec3 vWvertex;
out vec3 vWnormal;


void main(){
	vWvertex = vec3(model * vertex);
	vWnormal = mat3(transpose(inverse(model))) * normal;
	vUv0 = uv0;
	gl_Position = modelViewProjMat * vertex;
}

#version 330 core

in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;  
uniform float tiempo;        
out vec2 vUv0;
out vec2 vUv1;


void main(){
	vUv0 = uv0;
	vUv1 = vUv0;
	vUv1.t = vUv0.t;
	vUv1.s = uv0.s - tiempo ;
	gl_Position = modelViewProjMat * vertex;
}

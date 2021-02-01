#version 330 core

in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float SinTiempo;
out vec2 vUv0;
out vec2 vUv1;


void main(){
	vUv0 = uv0;
	
	float ZF = SinTiempo * 0.25 + 0.75;
    vUv1 = (uv0 - 0.5) * ZF + 0.5;
	
	gl_Position = modelViewProjMat * vertex;
}

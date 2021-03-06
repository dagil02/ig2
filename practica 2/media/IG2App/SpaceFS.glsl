#version 330 core

uniform sampler2D texturaL;
uniform sampler2D texturaM;
in vec2 vUv0;
in vec2 vUv1;
out vec4 fFragColor;

void main(){
	vec3 colorL = vec3(texture(texturaL, vUv0));
	vec3 colorM = vec3(texture(texturaM, vUv1));
	vec3 color = colorL * colorM;
	fFragColor = vec4(color, 1.0);
}
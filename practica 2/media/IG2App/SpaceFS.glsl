#version 330 core

uniform sampler2D textura0;
uniform sampler2D textura1;
//uniform float FB;
//uniform float intLuzAmb;
in vec2 vUv0;
in vec2 vUv1;
out vec4 fFragColor;

void main(){
	vec3 color0 = vec3(texture(textura0, vUv0));
	vec3 color1 = vec3(texture(textura1, vUv1));
	vec3 color = color0*color1;
	fFragColor = vec4(color, 1.0);
}
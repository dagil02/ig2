#version 330 core

in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform mat4 modelViewMat;
uniform mat4 normalMat;

out vec2 vUv0;
out vec3 vVertex;
out vec3 vNormal;

void main()
{
	vUv0 = uv0;
	gl_Position = modelViewProjMat * vertex;
	vNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));
	vVertex = vec3(modelViewMat * vertex);
}
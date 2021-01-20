#version 330 core 

layout (triangles) in; 	
layout (line_strip, max_vertices = 6) out;	

in vec3 gNormal[]; 

out vec3 vColor; 	

const float SIZE = 50; 

uniform mat4 modelViewProjMat;

void generateLine(int index) { 
	
	vColor = vec3 (1.0, 0.0, 0.0);
	gl_Position = modelViewProjMat * gl_in[index].gl_Position;
	EmitVertex();

	vColor = vec3 (1.0, 1.0, 0.0);
	gl_Position = modelViewProjMat * (gl_in[index].gl_Position	+ vec4(gNormal[index],0) * SIZE);
	EmitVertex(); 

	EndPrimitive(); 
}

void main()
{
	for (int i=0; i<3; ++i)
		generateLine(i);

}
#version 330 core


uniform sampler2D textura0;
uniform sampler2D textura1;
uniform vec4 InColor;
uniform vec4 OutColor;
uniform float Flipping;
in vec2 vUv0;
out vec4 fFragColor;

in vec3 vWvertex;
in vec3 vWnormal;

uniform vec3 lightPosition;
uniform vec3 lightDiffuse;

void main(){
	//LUZ
	vec3 norm = normalize(vWnormal);
	vec3 color1 = vec3(texture(textura1, vUv0));
	
	if( color1.r > 0.6 ){
		discard;
	}
	
	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;
	
	
	
	if(frontFacing){
		
		float diff = max(dot(norm,lightPosition),0.0);
		vec3 diffuse = diff*lightDiffuse;
		vec3 result0 = diffuse * texture(textura0, vUv0).rgb;
		
		fFragColor = OutColor * vec4(result0,1);
		
		
	} else {
		
		float diff = max(dot(-norm,lightPosition),0.0);
		vec3 diffuse = diff*lightDiffuse;
		vec3 result1 = diffuse * color1;
		fFragColor = InColor * vec4(result1,1);
	}
	
}
#version 450 core
out vec4 FragColor;

in vec3 oPos;
in vec2 TexCoord;

//uniform sampler2DRect ourTexture;
uniform sampler2D ourTexture;
uniform ivec2 texSize;


void main(){

	
	FragColor = texture(ourTexture, TexCoord);
	
	//FragColor = vec4(oPos.x, oPos.y, oPos.x/oPos.y , 1.0f);
}
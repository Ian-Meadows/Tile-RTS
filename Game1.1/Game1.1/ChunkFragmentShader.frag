#version 450 core
out vec4 FragColor;

in vec3 oPos;
flat in ivec2 unitInfo;
in vec2 texCoord;

uniform sampler2D chunkTexture;
uniform int chunkSize;

void main(){
	
	/*
	float posX = gl_FragCoord.x / chunkSize;

	//FragColor = vec4(oPos.x, oPos.y, oPos.x/oPos.y , 1.0f);

	if(mod(unitInfo.x,5) <= 2){
		FragColor = vec4(texCoord.x, oPos.y, unitInfo.y , 1.0f);
	}
	else{
		FragColor = vec4(1, oPos.y, 0 , 1.0f);
	}
	*/

	FragColor = texture(chunkTexture, texCoord);
	
	
	
}